#pragma once
#include "AttackBase.h"
#include <vector>
#include <map>
#include "core/strategies/IScalarMulStrategy.h"

namespace ecc {

class TimingAttack : public AttackBase {
public:
    using AttackBase::AttackBase;
    std::string name() const override;
public:
    void prepare(const AttackConfig& cfg) override;
    void execute() override;
    void analyze() override;
    AttackResult report() override;
private:
    BigInt targetKey_;
    unsigned samples_ = 1000;
    std::vector<double> naiveTimes_;
    std::vector<double> ladderTimes_;
    std::vector<int> hammingWeights_;
    std::map<int, std::vector<double>> byWeight_;
    std::shared_ptr<IScalarMulStrategy> naive_;
    std::shared_ptr<IScalarMulStrategy> ladder_;
    std::map<int, double> meanNaiveByWeight_;
    std::map<int, double> meanLadderByWeight_;
    double naiveCorrleation_ = 0.0;
    double ladderCorrelation_ = 0.0;
    bool naiveLeaks_ = false;
    bool ladderConstant_ = false;
};

} // namespace ecc
