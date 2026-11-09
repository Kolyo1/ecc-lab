#pragma once
#include "../bigint/BigInt.h"

namespace ecc {

struct Point {
    BigInt x;
    BigInt y;
    bool isInfinity = false;
};

} // namespace ecc
