#include "LogObserver.h"
#include <iostream>

namespace ecc {

void LogObserver::onValue(const std::string& label, const std::string& value) {
    std::cout << "[INFO] " << label << " = " << value << "\n";
}

void LogObserver::onTiming(const std::string& label, double microseconds) {
    std::cout << "[TIMING] " << label << ": " << microseconds << " us\n";
}

} // namespace ecc
