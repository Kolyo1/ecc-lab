#pragma once
#include "../bigint/BigInt.h"

namespace ecc {

struct Signature {
    BigInt r;
    BigInt s;
};

} // namespace ecc
