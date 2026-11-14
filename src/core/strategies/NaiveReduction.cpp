#include "NaiveReduction.h"

namespace ecc {
    BigInt NaiveReduction::reduce(const BigInt& x, const BigInt& modulus) const {
        BigInt r;

        if(x == BigInt("0")) return BigInt("0");
        if(modulus == BigInt("0")) throw std::invalid_argument("it must be positive");
        if(modulus == BigInt("1")) return BigInt(0);


        r = x % modulus;
        if(r < BigInt("0")) r = r + modulus;
        return r;
    }
} // namespace ecc
