#include "PointValidationDefense.h"

namespace ecc {

    PointValidationDefense::PointValidationDefense(std::shared_ptr<ProtocolBase> protokol)
        : protokol_(std::move(protokol)) {}

    std::string PointValidationDefense::name() const {
        return "PointValidation";
    }

    void PointValidationDefense::doApply(){
        protokol_->setValidatePoints(true);
    }

    void PointValidationDefense::doRemove(){
        protokol_->setValidatePoints(false);
    }

} // namespace ecc
