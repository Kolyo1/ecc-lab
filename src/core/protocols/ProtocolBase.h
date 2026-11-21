#pragma once
#include "KeyPair.h"
#include "Signature.h"
#include "IProtocolState.h"
#include "../curves/ICurve.h"
#include <memory>

namespace ecc {

class ProtocolBase {
public:
    ProtocolBase(std::shared_ptr<ICurve> curve, std::shared_ptr<IScalarMulStrategy> strategy);
    virtual ~ProtocolBase() = default;
    void run();
    const KeyPair& keyPair() const { return keyPair_; }
    KeyPair& keyPair() { return keyPair_; }
    std::shared_ptr<ICurve> curve() const { return curve_; }
    void setCurve(std::shared_ptr<ICurve> c) { curve_ = std::move(c); }
    void setValidatePoints(bool on) { validatePoints_ = on; }
    bool validatePoints() const { return validatePoints_; }
protected:
    virtual void generateKeys() = 0;
    virtual void performStep() = 0;
    virtual bool validate() const = 0;
    void transitionTo(std::unique_ptr<IProtocolState> next);
    std::shared_ptr<ICurve> curve_;
    std::shared_ptr<IScalarMulStrategy> strategy_;
    std::unique_ptr<IProtocolState> state_;
    KeyPair keyPair_;
    bool validatePoints_ = false;
};

} // namespace ecc
