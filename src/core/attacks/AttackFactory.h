#pragma once
#include "IAttack.h"
#include "../curves/ICurve.h"
#include "../protocols/ProtocolBase.h"
#include <string>
#include <memory>

namespace ecc {

class AttackFactory {
public:
    static std::unique_ptr<IAttack> create(const std::string& name, std::shared_ptr<ICurve> curve, std::shared_ptr<ProtocolBase> protocol);
};

} // namespace ecc
