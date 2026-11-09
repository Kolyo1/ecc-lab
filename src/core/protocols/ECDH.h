#pragma once
#include "ProtocolBase.h"

namespace ecc {

class ECDH : public ProtocolBase {
public:
    using ProtocolBase::ProtocolBase;
protected:
    void generateKeys() override;
    void performStep() override;
    bool validate() const override;
};

} // namespace ecc
