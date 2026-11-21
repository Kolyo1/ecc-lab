#pragma once
#include "AttackBase.h"

namespace ecc {

class NonceReuseAttack : public AttackBase {
public:
    using AttackBase::AttackBase;
    std::string name() const override;
public:
    void prepare(const AttackConfig& cfg) override;
    void execute() override;
    void analyze() override;
    AttackResult report() override;
private:
    std::string m1_, m2_;
    BigInt r_, s1_, s2_, z1_, z2_;
    BigInt targetKey_;
    BigInt recoveredD_;
};

} // namespace ecc
