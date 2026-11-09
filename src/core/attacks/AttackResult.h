#pragma once
#include "../bigint/BigInt.h"
#include <string>
#include <vector>

namespace ecc {

struct AttackResult {
    bool success = false;
    BigInt recoveredKey;
    std::vector<std::string> steps;
    double elapsedMs = 0.0;
};

} // namespace ecc
