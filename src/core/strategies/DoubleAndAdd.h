#pragma once
#include "IScalarMulStrategy.h"

namespace ecc {

class DoubleAndAdd : public IScalarMulStrategy {
public:
    Point multiply(const ICurve& curve, const BigInt& k, const Point& P) const override;
    const char* name() const override;
};

} // namespace ecc
