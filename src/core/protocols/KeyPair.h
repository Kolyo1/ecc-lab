#pragma once
#include "../bigint/BigInt.h"
#include "../curves/Point.h"

namespace ecc {

struct KeyPair {
    BigInt privateKey;
    Point  publicKey;
};

} // namespace ecc
