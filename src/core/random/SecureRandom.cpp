#include "SecureRandom.h"
#include <openssl/rand.h>
#include <stdexcept>
#include <string>

namespace ecc {

std::vector<unsigned char> SecureRandom::randomBytes(std::size_t n) {
    std::vector<unsigned char> buf(n);
    if (RAND_bytes(buf.data(), static_cast<int>(n)) != 1) {
        throw std::runtime_error("RAND_bytes failed");
    }
    return buf;
}

BigInt SecureRandom::inRange(const BigInt& low, const BigInt& high) {
    BigInt range = high - low + BigInt("1");
    std::size_t bits = range.bitLength();
    std::size_t numBytes = (bits + 7) / 8;

    while (true) {
        auto bytes = randomBytes(numBytes);
        BigInt r("0");
        for (unsigned char c : bytes) {
            r = r * BigInt("256") + BigInt(std::to_string(c));
        }
        // mask to `bits` bits to reduce retries (optional)
        if (r < range) {
            return low + r;
        }
    }
}

} // namespace ecc
