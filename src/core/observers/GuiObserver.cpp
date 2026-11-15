#include "GuiObserver.h"

namespace ecc {

GuiObserver::GuiObserver(ValueCallback onValue, TimingCallback onTiming)
    : onValue_(std::move(onValue)), onTiming_(std::move(onTiming)) {}

void GuiObserver::onValue(const std::string& label, const std::string& value) {
    if (onValue_) onValue_(label, value);
}

void GuiObserver::onTiming(const std::string& label, double microseconds) {
    if (onTiming_) onTiming_(label, microseconds);
}

} // namespace ecc
