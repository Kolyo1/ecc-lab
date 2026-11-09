#pragma once
#include "IDefense.h"

namespace ecc {

class DefenseBase : public IDefense {
public:
    void apply() final;       // template method
    void remove() final;
    bool isActive() const override;
protected:
    virtual void doApply() = 0;
    virtual void doRemove() = 0;
private:
    bool active_ = false;
};

} // namespace ecc
