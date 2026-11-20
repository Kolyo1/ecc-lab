#include "AttackBase.h"
#include <chrono>

namespace ecc {
    AttackResult AttackBase::run(const AttackConfig& cfg){
        auto start = std::chrono::high_resolution_clock::now();

        prepare(cfg);
        execute();
        analyze();
        AttackResult result = report();

        auto end = std::chrono::high_resolution_clock::now();
        result.elapsedMs = std::chrono::duration<double, std::milli>(end - start).count();

        notifyValue("attack", name());
        notifyValue("success", result.success ? "true" : "false");
        notifyTiming(name(), result.elapsedMs * 1000.0);

        return result;
    }
} // namespace ecc
