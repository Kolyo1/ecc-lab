#pragma once
#include "IObserver.h"

namespace ecc {

class TimingObserver : public IObserver {
public:
    void onValue(const std::string& label, const std::string& value) override;
    void onTiming(const std::string& label, double microseconds) override;
};

} // namespace ecc
