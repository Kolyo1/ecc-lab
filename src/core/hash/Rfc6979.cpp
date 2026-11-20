#include "Rfc6979.h"
#include "core/random/SecureRandom.h"

namespace ecc {

BigInt Rfc6979::generate(const BigInt& /*d*/, const std::vector<unsigned char>& /*h*/, const BigInt& n) {
    // TODO: implement HMAC-DRBG (RFC 6979). Fallback to random for now.
    return SecureRandom().inRange(BigInt("1"), n - BigInt("1"));
}

} // namespace ecc
