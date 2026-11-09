#pragma once
#include "ICurve.h"
#include <string>
#include <vector>
#include <memory>
#include <functional>

namespace ecc {

class CurveRegistry {
public:
    using Creator = std::function<std::unique_ptr<ICurve>()>;
    static CurveRegistry& instance();
    void registerCurve(const std::string& name, Creator c);
    std::unique_ptr<ICurve> get(const std::string& name) const;
    std::vector<std::string> list() const;
private:
    CurveRegistry() = default;
};

} // namespace ecc
