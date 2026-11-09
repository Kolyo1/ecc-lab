#pragma once
#include "IAttack.h"
#include <vector>
#include <memory>

namespace ecc {

class AttackBundle : public IAttack {
public:
    void add(std::shared_ptr<IAttack> a);
    AttackResult run(const AttackConfig& cfg) override;
    std::string name() const override;
private:
    std::vector<std::shared_ptr<IAttack>> children_;
};

} // namespace ecc
