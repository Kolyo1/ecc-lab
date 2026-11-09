#pragma once
#include <functional>
#include <future>
#include <vector>
#include <thread>

namespace ecc {

class ThreadPool {
public:
    explicit ThreadPool(unsigned threads);
    ~ThreadPool();
    template <class F> auto submit(F&& task);
    void shutdown();
private:
    std::vector<std::thread> workers_;
};

} // namespace ecc
