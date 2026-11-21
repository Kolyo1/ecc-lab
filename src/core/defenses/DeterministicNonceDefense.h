#pragma once
#include "DefenseBase.h"
#include "core/protocols/ECDSA.h"

namespace ecc {

class DeterministicNonceDefense : public DefenseBase {
public:
    explicit DeterministicNonceDefense(std::shared_ptr<ECDSA> ecdsa);
    std::string name() const override;
protected:
    void doApply() override;
    void doRemove() override;
private:
    std::shared_ptr<ECDSA> ecdsa_;
};

} // namespace ecc
