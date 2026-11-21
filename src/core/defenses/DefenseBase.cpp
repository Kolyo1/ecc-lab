#include "DefenseBase.h"

namespace ecc {

void DefenseBase::apply() {
    active_ = true;
    doApply();
}

void DefenseBase::remove() {
    active_ = false;
    doRemove();
}

bool DefenseBase::isActive() const {
    return active_;
}

} // namespace ecc
