#pragma once
#include "CurveParams.h"

namespace ecc {

class CurveParamsBuilder {
public:
    CurveParamsBuilder& name(const std::string&);
    CurveParamsBuilder& field(const BigInt& p);
    CurveParamsBuilder& coefficients(const BigInt& a, const BigInt& b);
    CurveParamsBuilder& generator(const Point& G);
    CurveParamsBuilder& order(const BigInt& n);
    CurveParamsBuilder& cofactor(const BigInt& h);
    CurveParams build() const;
private:
    CurveParams params_;
};

} // namespace ecc
