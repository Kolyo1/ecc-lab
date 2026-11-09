#pragma once
#include <string>
#include <vector>

namespace ecc {

class CliApp {
public:
    int run(const std::vector<std::string>& args);
    // one command per GUI demo
    int cmdInvalidCurve(const std::vector<std::string>& args);
    int cmdPohligHellman(const std::vector<std::string>& args);
    int cmdTiming(const std::vector<std::string>& args);
    int cmdNonceReuse(const std::vector<std::string>& args);
    int cmdBenchmark(const std::vector<std::string>& args);
};

} // namespace ecc
