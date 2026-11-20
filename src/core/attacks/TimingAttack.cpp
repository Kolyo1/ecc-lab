#include "TimingAttack.h"
#include <chrono>
#include "core/strategies/DoubleAndAdd.h"
#include "core/strategies/MontgomeryLadder.h"
#include "core/random/SecureRandom.h"

namespace ecc {
    void TimingAttack::prepare(const AttackConfig& cfg){
        targetKey_ = cfg.targetKey;
        samples_ = cfg.samples;
        naive_ = std::make_shared<DoubleAndAdd>();
        ladder_ = std::make_shared<MontgomeryLadder>();

        naiveTimes_.clear();
        ladderTimes_.clear();
        hammingWeights_.clear();
        byWeight_.clear();

        Point G = curve_->params().G;
        for(int i = 0; i < 10; ++i){
            curve_->setScalarMulStrategy(naive_);
            curve_->scalarMul(BigInt("42"), G);
            curve_->setScalarMulStrategy(ladder_);
            curve_->scalarMul(BigInt("42"), G);
        }
    } 

    void TimingAttack::execute(){
        const BigInt& n = curve_->params().n;
        const Point& G = curve_->params().G;
        
        naiveTimes_.clear();
        ladderTimes_.clear();
        hammingWeights_.clear();
        byWeight_.clear();

        std::vector<BigInt> scalars(samples_);

        for(unsigned i = 0; i < samples_; ++i){
            BigInt k = SecureRandom().inRange(BigInt("1"), n - BigInt("1"));
            scalars[i] = k;
            int hw = 0;
            BigInt tmp = k;
            while(tmp > BigInt("0")) { if(tmp.testBit(0)) ++hw; tmp = tmp >> 1; }
            hammingWeights_.push_back(hw);

            curve_->setScalarMulStrategy(naive_);
            for(unsigned i = 0; i < samples_; ++i){
                auto t0 = std::chrono::high_resolution_clock::now();
                curve_->scalarMul(scalars[i], G);
                auto t1 = std::chrono::high_resolution_clock::now();
                double us = std::chrono::duration<double, std::micro>(t1 - t0).count();
                naiveTimes_.push_back(us);
                byWeight_[hammingWeights_[i]].push_back(us);
            }

            curve_->setScalarMulStrategy(ladder_);
            for(unsigned i = 0; i < samples_; ++i){
                auto t0 = std::chrono::high_resolution_clock::now();
                curve_->scalarMul(scalars[i], G);
                auto t1 = std::chrono::high_resolution_clock::now();
                double us = std::chrono::duration<double, std::micro>(t1 - t0).count();
                ladderTimes_.push_back(us);
            }
        }
    }

    void TimingAttack::analyze(){
        std::map<int, std::vector<double>> byWeight;
        for(std::size_t i = 0; i < samples_; ++i){
            byWeight[hammingWeights_[i]].push_back(naiveTimes_[i]);
        }
        for(const auto& [w, times] : byWeight){
            double sum = 0.0;
            for(double t : times) sum += t;
            meanLadderByWeight_[w] = times.empty() ? 0.0 : sum / times.size();
        }

        std::map<int, std::vector<double>> byWeightLadder;
        for(std::size_t i = 0; i < samples_; ++i){
            byWeightLadder[hammingWeights_[i]].push_back(ladderTimes_[i]);
        }
        for(const auto& [w, times] : byWeightLadder){
            double sum = 0.0;
            for(double t : times) sum += t;
            meanLadderByWeight_[w] = times.empty() ? 0.0 : sum / times.size();
        }

        if(meanNaiveByWeight_.size() >= 2){
            auto itMin = meanNaiveByWeight_.begin();
            auto itMax = std::prev(meanNaiveByWeight_.end());
            double base = itMin->second;
            naiveCorrleation_ = (base > 0) ? (itMax->second - base) / base : 0.0;
            naiveLeaks_ = (naiveCorrleation_ > 0.05);
        }

        if(meanLadderByWeight_.size() >= 2){
            auto itMin = meanLadderByWeight_.begin();
            auto itMax = std::prev(meanLadderByWeight_.end());
            double base = itMin->second;
            ladderCorrelation_ = (base > 0) ? (itMax->second - base) / base : 0.0;
            ladderConstant_ = (std::abs(ladderCorrelation_) < 0.05);
        }

        success_ = naiveLeaks_ && ladderConstant_;
    }

    AttackResult TimingAttack::report(){
        AttackResult r;
        r.success = success_;
        r.steps = {
            "Collected " + std::to_string(samples_) + " timing samples",
            std::string("Naive: ") + (naiveLeaks_ ? "LEAK detected (timing ∝ Hamming weight)" : "no leak"),
            std::string("Ladder: ") + (ladderConstant_ ? "constant-time (flat)" : "NOT constant"),
        };
        return r;
    }
} // namespace ecc
