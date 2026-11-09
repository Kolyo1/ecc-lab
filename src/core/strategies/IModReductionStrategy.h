#pragma once
#include "../bigint/BigInt.h"

namespace ecc {

class IModReductionStrategy {
public:
    virtual ~IModReductionStrategy() = default;
    virtual BigInt reduce(const BigInt& x, const BigInt& modulus) const = 0;
    virtual const char* name() const = 0;
};

} // namespace ecc
