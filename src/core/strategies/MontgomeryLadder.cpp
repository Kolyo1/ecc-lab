#include "MontgomeryLadder.h"

namespace ecc {
    Point MontgomeryLadder::multiply(const ICurve& curve, const BigInt& k, const Point& P) const{
        Point R0 = curve.identity();
        Point R1 = P;
        for(int i = static_cast<int>(k.bitLength())-1; i >= 0; i--){
            if(!k.testBit(i)) {
                R1 = curve.add(R0,R1);
                R0 = curve.dbl(R0);
            }
            else{
                R0 = curve.add(R0,R1);
                R1 = curve.dbl(R1);
            }
            
        }
        return R0;
    }
} // namespace ecc
