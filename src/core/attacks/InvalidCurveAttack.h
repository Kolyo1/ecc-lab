#pragma once
#include "AttackBase.h"
#include "core/math/Crt.h"

namespace ecc {

class InvalidCurveAttack : public AttackBase {
public:
    using AttackBase::AttackBase;
    std::string name() const override;
public:
    void prepare(const AttackConfig& cfg) override;
    void execute() override;
    void analyze() override;
    AttackResult report() override;
private:
    std::vector<std::pair<Point, BigInt>> weakPoints_;
    std::vector<BigInt> residues_;
    BigInt recoveredD_;
    BigInt targetD_;
};

} // namespace ecc
