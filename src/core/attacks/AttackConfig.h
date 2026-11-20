#pragma once
#include "../bigint/BigInt.h"
#include "../curves/Point.h"
#include <string>

namespace ecc {

struct AttackConfig {
    std::string attackName;
    unsigned threads = 1;
    unsigned samples = 0;
    BigInt   targetKey;        // private key d (demo)
    Point    targetPublicKey;  // Q = d*G
};

} // namespace ecc
