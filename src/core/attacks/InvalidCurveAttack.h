#pragma once
#include "AttackBase.h"

namespace ecc {

class InvalidCurveAttack : public AttackBase {
public:
    using AttackBase::AttackBase;
    std::string name() const override;
protected:
    void prepare(const AttackConfig& cfg) override;
    void execute() override;
    void analyze() override;
    AttackResult report() override;
};

} // namespace ecc
