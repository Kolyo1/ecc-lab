#include "InvalidCurveAttack.h"

namespace ecc {
    void InvalidCurveAttack::prepare(const AttackConfig& cfg) {
        targetPublicKey_ = cfg.targetPublicKey;
        targetD_ = cfg.targetKey;   // the real d (demo only)
        weakPoints_.clear();
        weakPoints_.push_back({ Point{ BigInt("0"), BigInt("0"), false }, BigInt("2") });
    }
    void InvalidCurveAttack::execute(){
        residues_.clear();
        for(const auto& [P, q] : weakPoints_) {
            Point S = curve_->scalarMul(targetD_, P);

            BigInt residue("0");
            Point acc = curve_->identity();

            for(BigInt i("0"); i < q; i = i + BigInt("1")){
                if(acc.x == S.x && acc.y == S.y){ residue = i; break;}
                acc = curve_->add(acc, P);
            }
            residues_.push_back(residue);
        }
    }
    void InvalidCurveAttack::analyze(){
        std::vector<BigInt> moduli;
        for(const auto& [P, q] : weakPoints_) moduli.push_back(q);

        recoveredD_ = crt(residues_, moduli);

        Point Q = curve_->scalarMul(recoveredD_, curve_->params().G);
        success_ = (Q.x == targetPublicKey_.x && Q.y == targetPublicKey_.y);
    }

    AttackResult InvalidCurveAttack::report(){
        AttackResult r;
        r.success = success_;
        r.recoveredKey = recoveredD_;
        r.steps = {
        "Found off-curve point P of order q",
        "Victim computed S = d * P (no validation)",
        "Brute-forced d mod q",
        "CRT-combined residues into full key",
        success_ ? "Recovered key verified: d*G == Q" : "Verification failed"
        };
        return r;
    }
std::string InvalidCurveAttack::name() const { return "InvalidCurve"; }

} // namespace ecc
