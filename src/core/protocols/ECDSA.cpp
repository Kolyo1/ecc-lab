#include "ECDSA.h"
#include "core/hash/Sha256.h"
#include "core/random/SecureRandom.h"
#include <stdexcept>

namespace ecc {

static BigInt bytesToBigInt(const std::vector<unsigned char>& bytes, const BigInt& n) {
    BigInt r("0");
    for (unsigned char b : bytes) {
        r = r * BigInt("256") + BigInt(std::to_string(b));
    }
    // truncate to bit-length of n
    std::size_t bits = n.bitLength();
    // simple: reduce mod n
    return r % n;
}

static BigInt rfc6979K(const BigInt& d, const std::vector<unsigned char>& /*digest*/) {
    // TODO: implement HMAC-DRBG (RFC 6979). For now, fall back to random.
    return SecureRandom::inRange(BigInt("1"), BigInt("0"));  // placeholder
}

void ECDSA::generateKeys() {
    keyPair_.privateKey = SecureRandom::inRange(BigInt("1"), curve_->params().n - BigInt("1"));
    keyPair_.publicKey = curve_->scalarMul(keyPair_.privateKey, curve_->params().G);
}

Signature ECDSA::sign(const std::string& msg, const BigInt& d) {
    Sha256 hasher;
    hasher.update(msg);
    auto digest = hasher.finalize();
    BigInt z = bytesToBigInt(digest, curve_->params().n);

    while (true) {
        BigInt k = useDeterministic_
            ? rfc6979K(d, digest)
            : SecureRandom::inRange(BigInt("1"), curve_->params().n - BigInt("1"));

        Point R = curve_->scalarMul(k, curve_->params().G);
        BigInt r = R.x % curve_->params().n;
        if (r == BigInt("0")) continue;

        BigInt kInv = k.modInverse(curve_->params().n);
        BigInt s = (kInv * (z + r * d)) % curve_->params().n;
        if (s == BigInt("0")) continue;

        return Signature{ r, s };
    }
}

bool ECDSA::verify(const std::string& msg, const Signature& sig, const Point& Q) {
    const BigInt& n = curve_->params().n;
    if (sig.r < BigInt("1") || sig.r >= n) return false;
    if (sig.s < BigInt("1") || sig.s >= n) return false;

    Sha256 hasher;
    hasher.update(msg);
    auto digest = hasher.finalize();
    BigInt z = bytesToBigInt(digest, n);

    BigInt w = sig.s.modInverse(n);
    BigInt u1 = (z * w) % n;
    BigInt u2 = (sig.r * w) % n;

    Point P = curve_->add(
        curve_->scalarMul(u1, curve_->params().G),
        curve_->scalarMul(u2, Q)
    );

    if (P.isInfinity) return false;
    return (P.x % n) == sig.r;
}

void ECDSA::performStep() {
    signature_ = sign(msg_, keyPair_.privateKey);
    valid_ = verify(msg_, signature_, peerPublicKey_);
}

bool ECDSA::validate() const {
    return valid_;
}

} // namespace ecc