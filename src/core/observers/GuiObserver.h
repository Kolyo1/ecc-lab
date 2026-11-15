#pragma once
#include "IObserver.h"
#include <functional>

namespace ecc {

class GuiObserver : public IObserver {
public:
    using ValueCallback = std::function<void(const std::string&, const std::string&)>;
    using TimingCallback = std::function<void(const std::string&, double)>;
    explicit GuiObserver(ValueCallback onValue, TimingCallback onTiming);
    void onValue(const std::string& label, const std::string& value) override;
    void onTiming(const std::string& label, double microseconds) override;
private:
    ValueCallback onValue_;
    TimingCallback onTiming_;
};

} // namespace ecc
