#pragma once
#include "AttackBase.h"
#include "core/math/Factorize.h"

namespace ecc {

class PohligHellmanAttack : public AttackBase {
public:
    using AttackBase::AttackBase;
    std::string name() const override;
protected:
    void prepare(const AttackConfig& cfg) override;
    void execute() override;
    void analyze() override;
    AttackResult report() override;
private:
    std::vector<std::pair<BigInt, int>> factors_;   // (prime, exponent)
    std::vector<BigInt> moduli_;                    // p_i^e_i per factor
    BigInt recoveredD_;        // d_i per factor
    std::vector<BigInt> residues_;
};

} // namespace ecc
