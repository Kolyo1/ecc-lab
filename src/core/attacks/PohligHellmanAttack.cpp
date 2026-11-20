#include "PohligHellmanAttack.h"
#include "core/math/Crt.h"
#include "core/math/Factorize.h"

namespace ecc {

void PohligHellmanAttack::prepare(const AttackConfig& cfg) {
    targetPublicKey_ = cfg.targetPublicKey;
    factors_ = Factorize::factorize(curve_->params().n);
    residues_.clear();
    moduli_.clear();
}

void PohligHellmanAttack::execute() {
    const BigInt& n = curve_->params().n;
    const Point& G = curve_->params().G;

    for (const auto& [p, e] : factors_) {
        BigInt pe("1");
        for (int i = 0; i < e; ++i) pe = pe * p;

        BigInt factor = n / pe;
        Point G_i = curve_->scalarMul(factor, G);
        Point Q_i = curve_->scalarMul(factor, targetPublicKey_);

        BigInt d_i("0");
        Point acc = curve_->identity();
        for (BigInt i("0"); i < pe; i = i + BigInt("1")) {
            if (acc.x == Q_i.x && acc.y == Q_i.y) { d_i = i; break; }
            acc = curve_->add(acc, G_i);
        }

        residues_.push_back(d_i);
        moduli_.push_back(pe);
    }
}

void PohligHellmanAttack::analyze() {
    recoveredD_ = crt(residues_, moduli_);
    Point Q = curve_->scalarMul(recoveredD_, curve_->params().G);
    success_ = (Q.x == targetPublicKey_.x && Q.y == targetPublicKey_.y);
}

AttackResult PohligHellmanAttack::report() {
    AttackResult r;
    r.success = success_;
    r.recoveredKey = recoveredD_;
    r.steps = { "Factored n", "Solved DLP per subgroup", "CRT combined" };
    return r;
}

std::string PohligHellmanAttack::name() const { return "PohligHellman"; }

} // namespace ecc
