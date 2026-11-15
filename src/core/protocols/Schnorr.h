#pragma once
#include "ProtocolBase.h"
#include <string>

namespace ecc {

class Schnorr : public ProtocolBase {
public:
    using ProtocolBase::ProtocolBase;
    void setMessage(const std::string& m) { msg_ = m; }
    void setPeerPublicKey(const Point& Q) { peerPublicKey_ = Q; }
    const Point& signatureR() const { return signatureR_; }
    const BigInt& signatureS() const { return signatureS_; }
    bool isValid() const { return valid_; }
protected:
    void generateKeys() override;
    void performStep() override;
    bool validate() const override;
private:
    Point signatureR_;
    BigInt signatureS_ = BigInt("0");
    Point peerPublicKey_;
    bool valid_ = false;
    std::string msg_;
};

} // namespace ecc
