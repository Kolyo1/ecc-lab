#pragma once
#include "ProtocolBase.h"
#include "Signature.h"
#include "KeyPair.h"
#include <string>
#include "core/hash/Rfc6979.h"

namespace ecc {

class ECDSA : public ProtocolBase {
public:
    using ProtocolBase::ProtocolBase;
    void setMessage(const std::string& m) { msg_ = m; }
    void setPeerPublicKey(const Point& Q) { peerPublicKey_ = Q; }
    void setDeterministic(bool on) { useDeterministic_ = on; }
    const Signature& signature() const { return signature_; }
    bool isValid() const { return valid_; }
public:
    void generateKeys() override;
    void performStep() override;
    bool validate() const override;
private:
    Signature sign(const std::string& msg, const BigInt& d);
    bool verify(const std::string& msg, const Signature& sig, const Point& Q);
    Signature signature_;
    Point peerPublicKey_;
    bool valid_ = false;
    bool useDeterministic_ = false;
    std::string msg_;
};

} // namespace ecc