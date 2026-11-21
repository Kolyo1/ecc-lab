#include "StrongCurveDefense.h"

namespace ecc {

StrongCurveDefense::StrongCurveDefense(std::shared_ptr<ProtocolBase> protocol,
                                     std::shared_ptr<ICurve> weakCurve)
    : protokol_(std::move(protocol)), weakCurve_(std::move(weakCurve)) {}

std::string StrongCurveDefense::name() const { return "StrongCurve"; }

void StrongCurveDefense::doApply() {
    protokol_->setCurve(CurveFactory::create("secp256k1"));
}

void StrongCurveDefense::doRemove() {
    protokol_->setCurve(weakCurve_);
}

} // namespace ecc
