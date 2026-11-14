#include "DoubleAndAdd.h"

namespace ecc {
    Point DoubleAndAdd::multiply(const ICurve& curve, const BigInt& k, const Point& P) const{
        Point R = curve.identity();
        for(i from bitLength(k)-1 down to 0){
            R = curve.dbl(R);
            if(k.testBit(i)){
                R = curve.add(R,P);
            }
        }
        return R;
    }
} // namespace ecc
