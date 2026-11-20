#pragma once
#include "core/bigint/BigInt.h"
#include <vector>
#include <utility>

namespace ecc {

class Factorize {
public:
    static std::vector<std::pair<BigInt, int>> factorize(const BigInt& n);
};

} // namespace ecc
