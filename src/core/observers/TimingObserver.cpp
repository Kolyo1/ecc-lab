#include "TimingObserver.h"

namespace ecc {

void TimingObserver::onValue(const std::string&, const std::string&) {
    // timing observer ignores values
}

void TimingObserver::onTiming(const std::string& label, double microseconds) {
    std::lock_guard<std::mutex> lock(mutex_);
    samples_[label].push_back(microseconds);
}

std::vector<double> TimingObserver::samples(const std::string& label) const {
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = samples_.find(label);
    if (it == samples_.end()) return {};
    return it->second;
}

void TimingObserver::clear() {
    std::lock_guard<std::mutex> lock(mutex_);
    samples_.clear();
}

} // namespace ecc
