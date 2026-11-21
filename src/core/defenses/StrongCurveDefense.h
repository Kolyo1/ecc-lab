#pragma once
#include "DefenseBase.h"
#include "core/protocols/ProtocolBase.h"
#include "core/curves/CurveFactory.h"
#include <memory>

namespace ecc {

class StrongCurveDefense : public DefenseBase {
public:
    explicit StrongCurveDefense(std::shared_ptr<ProtocolBase> protokol,
                                std::shared_ptr<ICurve> weakCurve);
    std::string name() const override;
protected:
    void doApply() override;
    void doRemove() override;
private:
    std::shared_ptr<ProtocolBase> protokol_;
    std::shared_ptr<ICurve> weakCurve_;
};

} // namespace ecc
