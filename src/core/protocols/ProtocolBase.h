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
    void run();                               // template method
protected:
    virtual void generateKeys() = 0;
    virtual void performStep() = 0;
    virtual bool validate() const = 0;
    void transitionTo(std::unique_ptr<IProtocolState> next);
    std::shared_ptr<ICurve> curve_;
    std::shared_ptr<IScalarMulStrategy> strategy_;
    std::unique_ptr<IProtocolState> state_;
};

} // namespace ecc
