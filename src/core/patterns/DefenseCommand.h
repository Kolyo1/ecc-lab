#pragma once
#include "ICommand.h"
#include "../defenses/Defender.h"
#include <string>

namespace ecc {

class DefenseCommand : public ICommand {
public:
    DefenseCommand(Defender& defender, std::string name, bool enable);
    void execute() override;
    void undo() override;
};

} // namespace ecc
