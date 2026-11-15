#include "EdwardsCurve.h"
#include <utility>

namespace ecc {

static BigInt mod(const BigInt& x, const BigInt& p) {
    BigInt r = x % p;
    if (r < BigInt("0")) r = r + p;
    return r;
}

static bool isIdentity(const Point& P) {
    return P.x == BigInt("0") && P.y == BigInt("1");
}

EdwardsCurve::EdwardsCurve(CurveParams params)
    : params_(std::move(params)), mul_(nullptr), red_(nullptr) {}

Point EdwardsCurve::negate(const Point& P) const {
    if (isIdentity(P)) return P;
    return Point{ mod(params_.p - P.x, params_.p), P.y, false };
}

bool EdwardsCurve::isOnCurve(const Point& P) const {
    if (isIdentity(P)) return true;
    BigInt x2 = mod(P.x * P.x, params_.p);
    BigInt y2 = mod(P.y * P.y, params_.p);
    BigInt lhs = mod(params_.a * x2 + y2, params_.p);
    BigInt rhs = mod(BigInt("1") + params_.b * x2 * y2, params_.p);
    return lhs == rhs;
}

Point EdwardsCurve::dbl(const Point& P) const {
    if (isIdentity(P)) return P;

    BigInt x2 = mod(P.x * P.x, params_.p);
    BigInt y2 = mod(P.y * P.y, params_.p);

    BigInt numXR = mod(BigInt("2") * P.x * P.y, params_.p);
    BigInt denXR = mod(params_.a * x2 + y2, params_.p);
    BigInt xR = mod(numXR * denXR.modInverse(params_.p), params_.p);

    BigInt numYR = mod(y2 - params_.a * x2, params_.p);
    BigInt denYR = mod(BigInt("2") - params_.a * x2 - y2, params_.p);
    BigInt yR = mod(numYR * denYR.modInverse(params_.p), params_.p);

    return Point{ xR, yR, false };
}

Point EdwardsCurve::add(const Point& P, const Point& Q) const {
    if (isIdentity(P)) return Q;
    if (isIdentity(Q)) return P;

    // P == -Q  => identity (0, 1)
    if (mod(P.x + Q.x, params_.p) == BigInt("0") && P.y == Q.y) {
        return Point{ BigInt("0"), BigInt("1"), false };
    }

    BigInt numXR = mod(P.x * Q.y + P.y * Q.x, params_.p);
    BigInt denXR = mod(BigInt("1") + params_.b * P.x * Q.x * P.y * Q.y, params_.p);
    BigInt xR = mod(numXR * denXR.modInverse(params_.p), params_.p);

    BigInt numYR = mod(P.y * Q.y - params_.a * P.x * Q.x, params_.p);
    BigInt denYR = mod(BigInt("1") - params_.b * P.x * Q.x * P.y * Q.y, params_.p);
    BigInt yR = mod(numYR * denYR.modInverse(params_.p), params_.p);

    return Point{ xR, yR, false };
}

Point EdwardsCurve::scalarMul(const BigInt& k, const Point& P) const {
    if (mul_) return mul_->multiply(*this, k, P);
    Point result{ BigInt("0"), BigInt("1"), false };   // identity
    Point base = P;
    BigInt e = k;
    while (e > BigInt("0")) {
        if (e.testBit(0)) result = add(result, base);
        base = dbl(base);
        e = e >> 1;
    }
    return result;
}

Point EdwardsCurve::identity() const { return Point{ BigInt("0"), BigInt("1"), false }; }

const CurveParams& EdwardsCurve::params() const { return params_; }
void EdwardsCurve::setScalarMulStrategy(std::shared_ptr<IScalarMulStrategy> s) { mul_ = std::move(s); }
void EdwardsCurve::setReductionStrategy(std::shared_ptr<IModReductionStrategy> s) { red_ = std::move(s); }

} // namespace ecc
