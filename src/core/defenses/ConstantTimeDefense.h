#pragma once
#include "DefenseBase.h"
#include "core/curves/ICurve.h"
#include <memory>

namespace ecc {

class ConstantTimeDefense : public DefenseBase {
public:
    explicit ConstantTimeDefense(std::shared_ptr<ICurve> curve);
    std::string name() const override;
protected:
    void doApply() override;
    void doRemove() override;
private:
    std::shared_ptr<ICurve> curve_;
};

} // namespace ecc
