#pragma once
#include "IAttack.h"
#include "../curves/ICurve.h"
#include "../protocols/ProtocolBase.h"
#include "../observers/ObservableSubject.h"
#include <memory>

namespace ecc {

class AttackBase : public IAttack, public ObservableSubject {
public:
    AttackBase(std::shared_ptr<ICurve> curve, std::shared_ptr<ProtocolBase> protocol);
    AttackResult run(const AttackConfig& cfg) final;   // template method
protected:
    virtual void prepare(const AttackConfig& cfg) = 0;
    virtual void execute() = 0;
    virtual void analyze() = 0;
    virtual AttackResult report() = 0;
    std::shared_ptr<ICurve> curve_;
    std::shared_ptr<ProtocolBase> protocol_;
};

} // namespace ecc
