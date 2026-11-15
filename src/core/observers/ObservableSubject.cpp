#include "ObservableSubject.h"
#include <algorithm>

namespace ecc {

void ObservableSubject::attach(std::shared_ptr<IObserver> o) {
    std::lock_guard<std::mutex> lock(mutex_);
    observers_.push_back(std::move(o));
}

void ObservableSubject::detach(const std::shared_ptr<IObserver>& o) {
    std::lock_guard<std::mutex> lock(mutex_);
    observers_.erase(std::remove(observers_.begin(), observers_.end(), o),
                     observers_.end());
}

void ObservableSubject::notifyValue(const std::string& label, const std::string& value) {
    std::vector<std::shared_ptr<IObserver>> copy;
    {
        std::lock_guard<std::mutex> lock(mutex_);
        copy = observers_;
    }
    for (auto& o : copy) o->onValue(label, value);
}

void ObservableSubject::notifyTiming(const std::string& label, double microseconds) {
    std::vector<std::shared_ptr<IObserver>> copy;
    {
        std::lock_guard<std::mutex> lock(mutex_);
        copy = observers_;
    }
    for (auto& o : copy) o->onTiming(label, microseconds);
}

} // namespace ecc
