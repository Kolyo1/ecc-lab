#pragma once
#include "../bigint/BigInt.h"
#include "Point.h"
#include <string>

namespace ecc {

struct CurveParams {
    std::string name;
    BigInt p;          // field modulus
    BigInt a, b;       // curve coefficients
    Point  G;          // generator
    BigInt n;          // order of G
    BigInt h;          // cofactor
};

} // namespace ecc
