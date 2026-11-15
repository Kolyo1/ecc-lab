#pragma once
#include "IObserver.h"
#include <string>
#include <vector>
#include <map>
#include <mutex>

namespace ecc {

class TimingObserver : public IObserver {
public:
    void onValue(const std::string& label, const std::string& value) override;
    void onTiming(const std::string& label, double microseconds) override;
    std::vector<double> samples(const std::string& label) const;
    void clear();
private:
    std::map<std::string, std::vector<double>> samples_;
    mutable std::mutex mutex_;
};

} // namespace ecc
