#pragma once
#include "IRandom.h"
#include <vector>
#include <cstddef>
#include "core/bigint/BigInt.h"

namespace ecc {

class SecureRandom : public IRandom {
public:
    std::vector<unsigned char> randomBytes(std::size_t n) override;
    BigInt inRange(const BigInt& low, const BigInt& high) override;
};

} // namespace ecc
