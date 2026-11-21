#pragma once
#include <functional>
#include <future>
#include <vector>
#include <thread>
#include <condition_variable>
#include <queue>
#include <mutex>

namespace ecc {

class ThreadPool {
public:
    explicit ThreadPool(unsigned threads);
    ~ThreadPool();
    template <class F> auto submit(F&& task) {
        using ReturnType = std::invoke_result_t<std::decay_t<F>>;
        auto pt = std::make_shared<std::packaged_task<ReturnType()>>(std::forward<F>(task));
        auto fut = pt->get_future();
        {
            std::lock_guard<std::mutex> lock(mutex_);
            tasks_.emplace([pt]() { (*pt)(); });
        }
        cv_.notify_one();
        return fut;
    }
    void shutdown();
    unsigned size() const { return static_cast<unsigned>(workers_.size()); }
private:
    std::vector<std::thread> workers_;
    std::queue<std::function<void()>> tasks_;
    std::mutex mutex_;
    std::condition_variable cv_;
    bool stop_ = false;
};

} // namespace ecc
