#pragma once
#include "ProtocolBase.h"

namespace ecc {

class ECDH : public ProtocolBase {
private:
    Point peerPublicKey_;
    Point sharedSecret_;
public:
    using ProtocolBase::ProtocolBase;
    void setPeerPublicKey(const Point& Q) { peerPublicKey_ = Q;}
    const Point& sharedSecret() {return sharedSecret_;}
public:
    void generateKeys() override;
    void performStep() override;
    bool validate() const override;
};

} // namespace ecc
