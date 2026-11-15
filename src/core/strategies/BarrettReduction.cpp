#include "BarrettReduction.h"
#include "core/bigint/BigInt.h"
#include <stdexcept>

namespace ecc {

BigInt BarrettReduction::reduce(const BigInt& x, const BigInt& modulus) const {
    if (modulus <= BigInt("0")) throw std::invalid_argument("modulus must be positive");
    if (modulus == BigInt("1")) return BigInt("0");
    if (x == BigInt("0")) return BigInt("0");

    BigInt xx = x;
    if (xx < BigInt("0")) {
        xx = xx % modulus;
        if (xx < BigInt("0")) xx = xx + modulus;
    }

    std::size_t k = modulus.bitLength();

    BigInt twoPow = BigInt("1") << (2 * k);
    BigInt mu = twoPow / modulus;

    BigInt q = (xx * mu) >> (2 * k);

    BigInt r = xx - q * modulus;

    while (r >= modulus) r = r - modulus;
    if (r < BigInt("0")) r = r + modulus;

    return r;
}

const char* BarrettReduction::name() const {
    return "Barrett";
}

} // namespace ecc
