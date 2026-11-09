#pragma once
#include <memory>
#include <string>

namespace ecc {

class ProtocolBase;
class IProtocolState {
public:
    virtual ~IProtocolState() = default;
    virtual void generateKey(ProtocolBase& ctx) = 0;
    virtual void sign(ProtocolBase& ctx) = 0;
    virtual void verify(ProtocolBase& ctx) = 0;
    virtual std::string name() const = 0;
};
class InitState;
class KeyGeneratedState;
class SignedState;
class VerifiedState;
class FailedState;

} // namespace ecc
