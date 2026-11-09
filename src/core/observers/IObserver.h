#pragma once
#include <string>

namespace ecc {

class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void onValue(const std::string& label, const std::string& value) = 0;
    virtual void onTiming(const std::string& label, double microseconds) = 0;
};

} // namespace ecc
