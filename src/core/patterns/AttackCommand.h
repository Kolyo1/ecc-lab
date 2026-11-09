#pragma once
#include "ICommand.h"
#include "../attacks/Attacker.h"

namespace ecc {

class AttackCommand : public ICommand {
public:
    AttackCommand(Attacker& attacker, AttackConfig cfg);
    void execute() override;
    void undo() override;
};

} // namespace ecc
