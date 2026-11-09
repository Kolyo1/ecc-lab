#pragma once
#include "ICurve.h"
#include <string>
#include <memory>

namespace ecc {

class CurveFactory {
public:
    static std::unique_ptr<ICurve> create(const std::string& name);
    static std::unique_ptr<ICurve> create(const CurveParams& params, const std::string& form);
};

} // namespace ecc
