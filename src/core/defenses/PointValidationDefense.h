#pragma once
#include "DefenseBase.h"
#include "core/protocols/ProtocolBase.h"
#include <memory>

namespace ecc {

class PointValidationDefense : public DefenseBase {
public:
    explicit PointValidationDefense(std::shared_ptr<ProtocolBase> protokol);
    std::string name() const override;
protected:
    void doApply() override;
    void doRemove() override;
private: 
    std::shared_ptr<ProtocolBase> protokol_;
    bool wasEnabled = false;
};

} // namespace ecc
