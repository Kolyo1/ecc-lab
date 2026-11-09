#pragma once
#include "ICurve.h"

namespace ecc {

class EdwardsCurve : public ICurve {
public:
    explicit EdwardsCurve(CurveParams params);
    Point add(const Point& P, const Point& Q) const override;
    Point dbl(const Point& P) const override;
    Point negate(const Point& P) const override;
    Point scalarMul(const BigInt& k, const Point& P) const override;
    bool  isOnCurve(const Point& P) const override;
    const CurveParams& params() const override;
    void setScalarMulStrategy(std::shared_ptr<IScalarMulStrategy> s) override;
    void setReductionStrategy(std::shared_ptr<IModReductionStrategy> s) override;
private:
    CurveParams params_;
    std::shared_ptr<IScalarMulStrategy> mul_;
    std::shared_ptr<IModReductionStrategy> red_;
};

} // namespace ecc
