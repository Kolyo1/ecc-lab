#pragma once
#include <functional>
#include <vector>
#include <string>

namespace ecc {

struct BenchmarkEntry { std::string label; unsigned threads; double ms; };
class BenchmarkRunner {
public:
    std::vector<BenchmarkEntry> measureSpeedup(std::function<void(unsigned threads)> workload, const std::vector<unsigned>& threadCounts);
};

} // namespace ecc
