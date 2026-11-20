#pragma once
#include "core/bigint/BigInt.h"
#include <vector>

namespace ecc {

class Rfc6979 {
public:
    static BigInt generate(const BigInt& d,
                          const std::vector<unsigned char>& h,
                          const BigInt& n);
};

} // namespace ecc
