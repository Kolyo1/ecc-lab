#pragma once
#include "../bigint/BigInt.h"
#include "../curves/Point.h"

namespace ecc {

class ICurve;
class IScalarMulStrategy {
public:
    virtual ~IScalarMulStrategy() = default;
    virtual Point multiply(const ICurve& curve, const BigInt& k, const Point& P) const = 0;
    virtual const char* name() const = 0;
};

} // namespace ecc
