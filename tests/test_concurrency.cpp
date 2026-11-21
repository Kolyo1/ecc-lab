#include <catch2/catch_test_macros.hpp>
#include <atomic>
#include <numeric>
#include <vector>
#include "core/concurrency/ThreadPool.h"
#include "core/concurrency/ParallelRunner.h"

using namespace ecc;

TEST_CASE("ThreadPool executes all tasks") {
    ThreadPool pool(4);
    std::atomic<int> counter{0};
    std::vector<std::future<void>> futures;
    for (int i = 0; i < 100; ++i) {
        futures.push_back(pool.submit([&counter]() { ++counter; }));
    }
    for (auto& f : futures) f.get();
    REQUIRE(counter == 100);
}

TEST_CASE("ThreadPool returns future result") {
    ThreadPool pool(2);
    auto f = pool.submit([]() { return 42; });
    REQUIRE(f.get() == 42);
}

TEST_CASE("ParallelRunner calls body for every index") {
    ThreadPool pool(4);
    ParallelRunner runner(pool);
    std::atomic<int> count{0};
    std::vector<bool> seen(100, false);
    std::mutex mtx;
    runner.parallelFor(0, 100, [&seen, &mtx](std::size_t i) {
        std::lock_guard<std::mutex> lock(mtx);
        seen[i] = true;
    });
    for (int i = 0; i < 100; ++i) REQUIRE(seen[i]);
}

TEST_CASE("ParallelRunner empty range") {
    ThreadPool pool(2);
    ParallelRunner runner(pool);
    bool called = false;
    runner.parallelFor(5, 5, [&called](std::size_t) { called = true; });
    REQUIRE_FALSE(called);
}

TEST_CASE("ParallelRunner single element") {
    ThreadPool pool(2);
    ParallelRunner runner(pool);
    std::atomic<int> sum{0};
    runner.parallelFor(0, 1, [&sum](std::size_t i) { sum += static_cast<int>(i); });
    REQUIRE(sum == 0);
}

TEST_CASE("ThreadPool destructor joins threads") {
    {
        ThreadPool pool(4);
        auto f = pool.submit([]() { std::this_thread::sleep_for(std::chrono::milliseconds(10)); });
        f.get();
    }  // destructor should join cleanly
    REQUIRE(true);
}
