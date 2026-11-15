#include "NaiveReduction.h"
#include "core/bigint/BigInt.h"
#include <stdexcept>

namespace ecc {

    BigInt NaiveReduction::reduce(const BigInt& x, const BigInt& modulus) const {
        if (modulus <= BigInt("0")) throw std::invalid_argument("modulus must be positive");
        if (modulus == BigInt("1")) return BigInt("0");
        if (x == BigInt("0")) return BigInt("0");

        BigInt r = x % modulus;
        if (r < BigInt("0")) r = r + modulus;
        return r;
    }

    const char* NaiveReduction::name() const {
        return "Naive";
    }

} // namespace ecc
