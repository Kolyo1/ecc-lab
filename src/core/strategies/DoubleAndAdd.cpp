#include "DoubleAndAdd.h"
#include "core/curves/ICurve.h"
#include "core/bigint/BigInt.h"

namespace ecc {

Point DoubleAndAdd::multiply(const ICurve& curve, const BigInt& k, const Point& P) const {
    Point R = curve.identity();
    for (int i = static_cast<int>(k.bitLength()) - 1; i >= 0; --i) {
        R = curve.dbl(R);
        if (k.testBit(static_cast<std::size_t>(i))) {
            R = curve.add(R, P);
        }
    }
    return R;
}

const char* DoubleAndAdd::name() const {
    return "DoubleAndAdd";
}

} // namespace ecc
