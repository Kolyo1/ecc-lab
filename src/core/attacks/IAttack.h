#pragma once
#include "AttackConfig.h"
#include "AttackResult.h"

namespace ecc {

class IAttack {
public:
    virtual ~IAttack() = default;
    virtual AttackResult run(const AttackConfig& cfg) = 0;
    virtual std::string name() const = 0;
};

} // namespace ecc
