#pragma once
#include <string>

namespace ecc {

class IDefense {
public:
    virtual ~IDefense() = default;
    virtual void apply() = 0;
    virtual void remove() = 0;
    virtual bool isActive() const = 0;
    virtual std::string name() const = 0;
};

} // namespace ecc
