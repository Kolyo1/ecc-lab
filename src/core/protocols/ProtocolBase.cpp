#include "ProtocolBase.h"

namespace ecc {

ProtocolBase::ProtocolBase(std::shared_ptr<ICurve> curve, std::shared_ptr<IScalarMulStrategy> strategy)
    : curve_(std::move(curve)), strategy_(std::move(strategy)), state_(nullptr) {}

void ProtocolBase::run() {
    generateKeys();
    performStep();
    validate();
}

void ProtocolBase::transitionTo(std::unique_ptr<IProtocolState> next) {
    state_ = std::move(next);
}

} // namespace ecc
