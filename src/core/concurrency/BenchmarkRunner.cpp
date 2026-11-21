#include "BenchmarkRunner.h"
#include "ThreadPool.h"
#include "ParallelRunner.h"
#include <chrono>
#include <string>
#include <vector>

namespace ecc {
    std::vector<BenchmarkEntry> BenchmarkRunner::measureSpeedup(std::function<void(unsigned threads)> workload, const std::vector<unsigned>& threadCounts){
        std::vector<BenchmarkEntry> results; 
        
        for(unsigned threads : threadCounts){
            ThreadPool pool(threads);
            ParallelRunner runner(pool);
            auto start = std::chrono::high_resolution_clock::now();
            workload(threads);
            
            auto end = std::chrono::high_resolution_clock::now();
            
            double elapsed = std::chrono::duration<double, std::milli>(end - start).count();
            results.push_back({std::to_string(threads) + "threads", threads, elapsed});
        }
        return results;
    }
} // namespace ecc
