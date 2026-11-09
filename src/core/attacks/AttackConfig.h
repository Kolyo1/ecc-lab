#pragma once
#include "../bigint/BigInt.h"
#include <string>

namespace ecc {

struct AttackConfig {
    std::string attackName;
    unsigned threads = 1;
    unsigned samples = 0;
    BigInt   targetKey;
};

} // namespace ecc
