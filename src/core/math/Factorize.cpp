#include "Factorize.h"

namespace ecc {

std::vector<std::pair<BigInt, int>> Factorize::factorize(const BigInt& n) {
    std::vector<std::pair<BigInt, int>> factors;
    BigInt remaining = n;
    BigInt p("2");

    while (p * p <= remaining) {
        if (remaining % p == BigInt("0")) {
            int e = 0;
            while (remaining % p == BigInt("0")) {
                remaining = remaining / p;
                ++e;
            }
            factors.push_back({ p, e });
        }
        if (p == BigInt("2")) p = BigInt("3");
        else p = p + BigInt("2");
    }

    if (remaining > BigInt("1")) {
        factors.push_back({ remaining, 1 });
    }
    return factors;
}

} // namespace ecc
