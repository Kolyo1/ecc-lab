#include "MontgomeryLadder.h"
#include "core/curves/ICurve.h"
#include "core/bigint/BigInt.h"

namespace ecc {

Point MontgomeryLadder::multiply(const ICurve& curve, const BigInt& k, const Point& P) const {
    Point R0 = curve.identity();
    Point R1 = P;
    for (int i = static_cast<int>(k.bitLength()) - 1; i >= 0; --i) {
        if (!k.testBit(static_cast<std::size_t>(i))) {
            R1 = curve.add(R0, R1);
            R0 = curve.dbl(R0);
        } else {
            R0 = curve.add(R0, R1);
            R1 = curve.dbl(R1);
        }
    }
    return R0;
}

const char* MontgomeryLadder::name() const {
    return "MontgomeryLadder";
}

} // namespace ecc
