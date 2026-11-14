#pragma once
#include "CurveParams.h"
#include "../strategies/IScalarMulStrategy.h"
#include "../strategies/IModReductionStrategy.h"
#include <memory>

namespace ecc {

class ICurve {
public:
    virtual ~ICurve() = default;
    virtual Point identity() const = 0;
    virtual Point add(const Point& P, const Point& Q) const = 0;
    virtual Point dbl(const Point& P) const = 0;
    virtual Point negate(const Point& P) const = 0;
    virtual Point scalarMul(const BigInt& k, const Point& P) const = 0;
    virtual bool  isOnCurve(const Point& P) const = 0;
    virtual const CurveParams& params() const = 0;
    virtual void setScalarMulStrategy(std::shared_ptr<IScalarMulStrategy> s) = 0;
    virtual void setReductionStrategy(std::shared_ptr<IModReductionStrategy> s) = 0;
};

} // namespace ecc
