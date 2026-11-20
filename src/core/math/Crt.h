#pragma once
#include "core/bigint/BigInt.h"
#include <vector>

namespace ecc {

BigInt crt(const std::vector<BigInt>& residues, const std::vector<BigInt>& moduli);

} // namespace ecc