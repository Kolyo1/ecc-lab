#include "WeierstrassCurve.h"
#include <utility>

namespace ecc {

static Point infinityPoint() {
    Point p;
    p.isInfinity = true;
    return p;
}

static BigInt mod(const BigInt& x, const BigInt& p) {
    BigInt r = x % p;
    if (r < BigInt("0")) r = r + p;
    return r;
}

WeierstrassCurve::WeierstrassCurve(CurveParams params)
    : params_(std::move(params)), mul_(nullptr), red_(nullptr) {}

Point WeierstrassCurve::negate(const Point& P) const {
    if (P.isInfinity) return P;
    return Point{ P.x, mod(params_.p - P.y, params_.p), false };
}

bool WeierstrassCurve::isOnCurve(const Point& P) const {
    if (P.isInfinity) return true;
    BigInt lhs = mod(P.y * P.y, params_.p);
    BigInt rhs = mod(P.x * P.x * P.x + params_.a * P.x + params_.b, params_.p);
    return lhs == rhs;
}

Point WeierstrassCurve::dbl(const Point& P) const {
    if (P.isInfinity) return infinityPoint();
    if (P.y == BigInt("0")) return infinityPoint();

    BigInt num = mod(BigInt("3") * P.x * P.x + params_.a, params_.p);
    BigInt den = mod(BigInt("2") * P.y, params_.p);
    BigInt lambda = mod(num * den.modInverse(params_.p), params_.p);

    BigInt xR = mod(lambda * lambda - BigInt("2") * P.x, params_.p);
    BigInt yR = mod(lambda * (P.x - xR) - P.y, params_.p);
    return Point{ xR, yR, false };
}

Point WeierstrassCurve::add(const Point& P, const Point& Q) const {
    if (P.isInfinity) return Q;
    if (Q.isInfinity) return P;
    if (P.x == Q.x) {
        if (P.y == Q.y) return dbl(P);
        return infinityPoint();   // P = -Q
    }

    BigInt num = mod(Q.y - P.y, params_.p);
    BigInt den = mod(Q.x - P.x, params_.p);
    BigInt lambda = mod(num * den.modInverse(params_.p), params_.p);

    BigInt xR = mod(lambda * lambda - P.x - Q.x, params_.p);
    BigInt yR = mod(lambda * (P.x - xR) - P.y, params_.p);
    return Point{ xR, yR, false };
}

Point WeierstrassCurve::scalarMul(const BigInt& k, const Point& P) const {
    if (mul_) {
        return mul_->multiply(*this, k, P);
    }
    Point result = infinityPoint();
    Point base = P;
    BigInt e = k;
    while (e > BigInt("0")) {
        if (e.testBit(0)) {
            result = add(result, base);
        }
        base = dbl(base);
        e = e >> 1;
    }
    return result;
}

const CurveParams& WeierstrassCurve::params() const { return params_; }

void WeierstrassCurve::setScalarMulStrategy(std::shared_ptr<IScalarMulStrategy> s) { mul_ = std::move(s); }

void WeierstrassCurve::setReductionStrategy(std::shared_ptr<IModReductionStrategy> s) { red_ = std::move(s); }

} // namespace ecc
