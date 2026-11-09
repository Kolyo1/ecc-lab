#pragma once
#include "DefenseBase.h"

namespace ecc {

class DeterministicNonceDefense : public DefenseBase {
public:
    std::string name() const override;
protected:
    void doApply() override;
    void doRemove() override;
};

} // namespace ecc
