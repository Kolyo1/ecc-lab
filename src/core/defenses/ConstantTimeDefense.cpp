#include "ConstantTimeDefense.h"
#include "core/strategies/MontgomeryLadder.h"
#include "core/strategies/DoubleAndAdd.h"

namespace ecc {
    ConstantTimeDefense::ConstantTimeDefense(std::shared_ptr<ICurve> curve)
        : curve_(std::move(curve)) {}

    std::string ConstantTimeDefense::name() const{
        return "ConstantTime";
    }

    void ConstantTimeDefense::doApply(){
        curve_->setScalarMulStrategy(std::make_shared<MontgomeryLadder>());
    }

    void ConstantTimeDefense::doRemove(){
        curve_->setScalarMulStrategy(std::make_shared<DoubleAndAdd>());
    }
} // namespace ecc
