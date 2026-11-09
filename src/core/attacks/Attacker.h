#pragma once
#include "IAttack.h"
#include <memory>

namespace ecc {

class Attacker {
public:
    void setAttack(std::shared_ptr<IAttack> a);
    AttackResult launch(const AttackConfig& cfg);
private:
    std::shared_ptr<IAttack> attack_;
};

} // namespace ecc
