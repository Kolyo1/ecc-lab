#include "DeterministicNonceDefense.h"

namespace ecc {

    DeterministicNonceDefense::DeterministicNonceDefense(std::shared_ptr<ECDSA> ecdsa)
        : ecdsa_(std::move(ecdsa)) {}

    std::string DeterministicNonceDefense::name() const{
        return "DeterministicNonce";
    }

    void DeterministicNonceDefense::doApply(){
        ecdsa_->setDeterministic(true);
    }

    void DeterministicNonceDefense::doRemove(){
        ecdsa_->setDeterministic(false);
    }
} // namespace ecc
