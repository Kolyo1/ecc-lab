#include "Attacker.h"

namespace ecc {
    void Attacker::setAttack(std::shared_ptr<IAttack> a){
        attack_ = std::move(a);
    }
    
    AttackResult Attacker::launch(const AttackConfig& cfg){
        if(!attack_) throw std::runtime_error("no attack set");
        return attack_->run(cfg);
    }
} // namespace ecc
