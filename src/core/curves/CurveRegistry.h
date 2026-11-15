#pragma once
#include "ICurve.h"
#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <map>

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
    std::map<std::string, Creator> creators_;
};

} // namespace ecc
