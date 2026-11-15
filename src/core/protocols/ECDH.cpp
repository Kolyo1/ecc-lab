#include "ECDH.h"
#include "core/random/SecureRandom.h"

namespace ecc {

void ECDH::generateKeys() {
    keyPair().privateKey = SecureRandom().inRange(BigInt("1"), curve_->params().n - BigInt("1"));
    keyPair().publicKey = curve_->scalarMul(keyPair().privateKey, curve_->params().G);
}

void ECDH::performStep() {
    sharedSecret_ = curve_->scalarMul(keyPair().privateKey, peerPublicKey_);
}

bool ECDH::validate() const {
    return !sharedSecret_.isInfinity;
}

} // namespace ecc
