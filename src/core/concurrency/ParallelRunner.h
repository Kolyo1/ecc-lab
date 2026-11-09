#pragma once
#include "ThreadPool.h"
#include <functional>

namespace ecc {

class ParallelRunner {
public:
    explicit ParallelRunner(ThreadPool& pool);
    void parallelFor(std::size_t begin, std::size_t end, std::function<void(std::size_t)> body);
private:
    ThreadPool& pool_;
};

} // namespace ecc
