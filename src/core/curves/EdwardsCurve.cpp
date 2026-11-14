#include "EdwardsCurve.h"

namespace ecc {

    static BigInt mod(const BigInt& x, const BigInt& p){
        BigInt r = x % p;
        if(r < BigInt("0")) r = r + p;
        return r;
    }
    
    static bool isIdentity(const Point& P) {
        return P.x == BigInt("0") && P.y == BigInt("1");
    }

    EdwardsCurve::EdwardsCurve(CurveParams parmas)
    : params_(std::move(params)), mul_(nullptr), red_(nullptr) {}

    Point EdwardsCurve::negate(const Point& P) const {
        if(P.x == BigInt("0") && P.y == BigInt("1")) return P;
        return Point {mod(params_.p - P.x, params_.p), P.y, false};
    }

    bool EdwardsCurve::isOnCurve(const Point& P) const{
        if(P.x == BigInt("0") && P.y == BigInt("1")) return true;

        BigInt x2 = mod(P.x * P.x, params_.p);
        BigInt y2 = mod(P.y * P.y, params_.p);
        BigInt lhs = mod(params_.a * x2 * y2, params_.p);
        BigInt rhs = mod(BigInt("1") + params_.b * x2 * y2, params_.p);
        return lhs == rhs;
    }

    Point EdwardsCurve::dbl(const Point& P) const{
        if(P.x == BigInt("0") && P.y == BigInt("1")) return P;

        BigInt x2 = mod(P.x * P.x ,params_.p);
        BigInt y2 = mod(P.y * P.y, params_.p);

        BigInt numXR = mod(BigInt("2") * P.x * P.y, params_.p);
        BigInt denXR = mod(params_.a * x2 + y2, params_.p);
        BigInt xR = mod(numXR * denXR.modInverse(params_.p), params_.p);

        BigInt numYR = mod(y2 - params_.a * x2, params_.p);
        BigInt denYR = mod(BigInt("2") - params_.p * x2 - y2, params_.p);
        BigInt yR = mod(numYR * denYR.modInverse(params_.p), params_.p);

        return Point {xR, yR, false};
    }
    
    Point EdwardsCurve::add(const Point& P, const Point& Q){
        if(P.x == BigInt("0") && P.y == BigInt("1")) return Q;
        if(Q.x == BigInt("0") && Q.y == BigInt("1")) return P;
        
        if(mod(P.x + Q.x, params_.p) == BigInt("0") && P.y == Q.y){
            return Point{BigInt("0"), BigInt("1"), false};
        }

        BigInt numXR = mod(P.x * Q.y + P.y * Q.x, params_.p);
        BigInt denXR = mod(BigInt("1") + params_.b * P.x * Q.x * P.y * Q.y, params_.p);
        BigInt xR = mod(numXR * denXR.modInverse(params_.p), params_.p);

        BigInt numYR = mod(P.y * Q.y - params_.a * P.x * Q.x, params_.p);
        BigInt denYR = mod(BigInt("1") - params_.b * P.x * Q.x * P.y * Q.y, params_.p);

        return Point{xR, yR, false};
    }

    Point MontgomeryCurve::scalarMul(const BigInt& k, const Point& P) const{
            if(mul_){
                return mul_->multiply(*this, k, P);
            }
            Point res = infinityPoint();
            Point base = P;
            BigInt e = k;
            while(e < BigInt("0")){
                if(e.testBit(1)){
                    res = add(res,base);
                }
                base = dbl(base);
                e = e>>1;
            }
            return res;    
    }

    const CurveParams& MontgomeryCurve::params() const { return params_; }

    void MontgomeryCurve::setScalarMulStrategy(std::shared_ptr<IScalarMulStrategy> s) { mul_ = std::move(s); }

    void MontgomeryCurve::setReductionStrategy(std::shared_ptr<IModReductionStrategy> s) { red_ = std::move(s); }

} // namespace ecc
