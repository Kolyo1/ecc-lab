#include "NonceReuseAttack.h"
#include "core/hash/SHA256.h"
#include "core/random/SecureRandom.h"

namespace ecc {

static BigInt toBigInt(const std::vector<unsigned char>& bytes) {
    BigInt r("0");
    for (unsigned char b : bytes) r = r * BigInt("256") + BigInt(std::to_string(b));
    return r;
}

void NonceReuseAttack::prepare(const AttackConfig& cfg) {
    const BigInt& n = curve_->params().n;
    const Point& G = curve_->params().G;

    targetPublicKey_ = cfg.targetPublicKey;

    // two messages
    m1_ = "message one";
    m2_ = "message two";

    // one nonce reused for both
    BigInt k = SecureRandom().inRange(BigInt("1"), n - BigInt("1"));

    // sign m1
    Point R = curve_->scalarMul(k, G);
    r_ = R.x % n;
    Sha256 h1; h1.update(m1_); auto d1 = h1.finalize();
    z1_ = toBigInt(d1) % n;
    s1_ = (k.modInverse(n) * (z1_ + r_ * cfg.targetKey)) % n;

    // sign m2 with SAME k
    Sha256 h2; h2.update(m2_); auto d2 = h2.finalize();
    z2_ = toBigInt(d2) % n;
    s2_ = (k.modInverse(n) * (z2_ + r_ * cfg.targetKey)) % n;
}

void NonceReuseAttack::execute() {
    const BigInt& n = curve_->params().n;

    // k = (z1 - z2) / (s1 - s2)  mod n
    BigInt kNum = (z1_ - z2_) % n;
    if (kNum < BigInt("0")) kNum = kNum + n;
    BigInt kDen = (s1_ - s2_) % n;
    if (kDen < BigInt("0")) kDen = kDen + n;
    BigInt k = (kNum * kDen.modInverse(n)) % n;

    // d = (s1 * k - z1) / r  mod n
    BigInt dNum = (s1_ * k - z1_) % n;
    if (dNum < BigInt("0")) dNum = dNum + n;
    BigInt dDen = r_ % n;
    recoveredD_ = (dNum * dDen.modInverse(n)) % n;
}

void NonceReuseAttack::analyze() {
    Point Q = curve_->scalarMul(recoveredD_, curve_->params().G);
    success_ = (Q.x == targetPublicKey_.x && Q.y == targetPublicKey_.y);
}

AttackResult NonceReuseAttack::report() {
    AttackResult r;
    r.success = success_;
    r.recoveredKey = recoveredD_;
    r.steps = { "k = (z1-z2)/(s1-s2)", "d = (s1*k - z1)/r" };
    return r;
}

std::string NonceReuseAttack::name() const { return "NonceReuse"; }

} // namespace ecc
