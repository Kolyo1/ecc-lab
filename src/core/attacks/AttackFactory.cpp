#include "AttackFactory.h"
#include "NonceReuseAttack.h"
#include "InvalidCurveAttack.h"
#include "PohligHellmanAttack.h"
#include "TimingAttack.h"

namespace ecc {

    std::unique_ptr<IAttack> AttackFactory::create(const std::string& name, std::shared_ptr<ICurve> curve, std::shared_ptr<ProtocolBase> protocol){
    if (name == "NonceReuse") return std::make_unique<NonceReuseAttack>(curve, protocol);
    if (name == "InvalidCurve") return std::make_unique<InvalidCurveAttack>(curve, protocol);
    if (name == "PohligHellman") return std::make_unique<PohligHellmanAttack>(curve, protocol);
    if (name == "Timing") return std::make_unique<TimingAttack>(curve, protocol);
    return nullptr;
    }

} // namespace ecc
