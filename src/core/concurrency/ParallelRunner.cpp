#include "ParallelRunner.h"
#include <algorithm>

namespace ecc {

ParallelRunner::ParallelRunner(ThreadPool& pool) : pool_(pool) {}

void ParallelRunner::parallelFor(std::size_t begin, std::size_t end,
                                std::function<void(std::size_t)> body) {
    if (begin >= end) return;

    unsigned numThreads = pool_.size();
    if (numThreads == 0) numThreads = 1;

    std::size_t total = end - begin;
    std::size_t chunkSize = (total + numThreads - 1) / numThreads;

    std::vector<std::future<void>> futures;
    for (unsigned t = 0; t < numThreads; ++t) {
        std::size_t chunkBegin = begin + t * chunkSize;
        if (chunkBegin >= end) break;
        std::size_t chunkEnd = std::min(chunkBegin + chunkSize, end);
        futures.push_back(pool_.submit([chunkBegin, chunkEnd, &body]() {
            for (std::size_t i = chunkBegin; i < chunkEnd; ++i) {
                body(i);
            }
        }));
    }

    for (auto& f : futures) f.get();
}

} // namespace ecc
