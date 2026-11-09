#pragma once
#include "IObserver.h"
#include <vector>
#include <memory>
#include <mutex>

namespace ecc {

class ObservableSubject {
public:
    void attach(std::shared_ptr<IObserver> o);
    void detach(const std::shared_ptr<IObserver>& o);
protected:
    void notifyValue(const std::string& label, const std::string& value);
    void notifyTiming(const std::string& label, double microseconds);
private:
    std::vector<std::shared_ptr<IObserver>> observers_;
    mutable std::mutex mutex_;
};

} // namespace ecc
