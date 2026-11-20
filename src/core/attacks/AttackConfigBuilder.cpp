#include "AttackConfigBuilder.h"

namespace ecc {

AttackConfigBuilder& AttackConfigBuilder::name(const std::string& n) {
    cfg_.attackName = n;
    return *this;
}

AttackConfigBuilder& AttackConfigBuilder::threads(unsigned t) {
    cfg_.threads = t;
    return *this;
}

AttackConfigBuilder& AttackConfigBuilder::samples(unsigned s) {
    cfg_.samples = s;
    return *this;
}

AttackConfigBuilder& AttackConfigBuilder::target(const BigInt& key) {
    cfg_.targetKey = key;
    return *this;
}

AttackConfigBuilder& AttackConfigBuilder::targetPub(const Point& pub) {
    cfg_.targetPublicKey = pub;
    return *this;
}

AttackConfig AttackConfigBuilder::build() const {
    return cfg_;
}

} // namespace ecc
