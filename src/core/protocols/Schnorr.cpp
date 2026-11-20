#include "Schnorr.h"
#include "core/hash/SHA256.h"
#include "core/random/SecureRandom.h"

namespace ecc {

void Schnorr::generateKeys() {
    keyPair().privateKey = SecureRandom().inRange(BigInt("1"), curve_->params().n - BigInt("1"));
    keyPair().publicKey = curve_->scalarMul(keyPair().privateKey, curve_->params().G);
}

void Schnorr::performStep() {
    BigInt k = SecureRandom().inRange(BigInt("1"), curve_->params().n - BigInt("1"));
    Point R = curve_->scalarMul(k, curve_->params().G);

    Sha256 hasher;
    hasher.update(R.x.toString());
    hasher.update(R.y.toString());
    hasher.update(msg_);
    auto digest = hasher.finalize();
    BigInt e = BigInt("0");
    for (unsigned char b : digest) e = e * BigInt("256") + BigInt(std::to_string(b));
    e = e % curve_->params().n;

    BigInt s = (k + e * keyPair().privateKey) % curve_->params().n;

    signatureR_ = R;
    signatureS_ = s;

    Point sG = curve_->scalarMul(s, curve_->params().G);
    Point eQ = curve_->scalarMul(e, keyPair().publicKey);
    Point Rp = curve_->add(sG, curve_->negate(eQ));

    valid_ = (Rp.x == R.x && Rp.y == R.y);
}

bool Schnorr::validate() const {
    return valid_;
}

} // namespace ecc
