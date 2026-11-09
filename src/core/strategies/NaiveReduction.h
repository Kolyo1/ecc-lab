#pragma once
#include "IModReductionStrategy.h"

namespace ecc {

class NaiveReduction : public IModReductionStrategy {
public:
    BigInt reduce(const BigInt& x, const BigInt& modulus) const override;
    const char* name() const override;
};

} // namespace ecc
