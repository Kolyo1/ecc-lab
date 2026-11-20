#pragma once
#include "AttackConfig.h"

namespace ecc {

class AttackConfigBuilder {
public:
    AttackConfigBuilder& name(const std::string&);
    AttackConfigBuilder& threads(unsigned);
    AttackConfigBuilder& samples(unsigned);
    AttackConfigBuilder& target(const BigInt&);
    AttackConfigBuilder& targetPub(const Point&);
    AttackConfig build() const;
private:
    AttackConfig cfg_;
};

} // namespace ecc
