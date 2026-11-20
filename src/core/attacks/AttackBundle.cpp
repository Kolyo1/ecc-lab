#include "AttackBundle.h"

namespace ecc {

    void AttackBundle::add(std::shared_ptr<IAttack> a){
        children_.push_back(std::move(a));
    }

    AttackResult AttackBundle::run(const AttackConfig& cfg){
        AttackResult result;
        result.success = true;
        auto start = std::chrono::high_resolution_clock::now();

        for(auto& child: children_){
            auto r = child->run(cfg);
            result.success = result.success && r.success;
            result.steps.insert(result.steps.end(), r.steps.begin(), r.steps.end());
            if(r.success && result.recoveredKey == BigInt("0")){
                result.recoveredKey = r.recoveredKey;
            }
        }

        auto end = std::chrono::high_resolution_clock::now();
        result.elapsedMs = std::chrono::duration<double, std::milli>(end - start).count();
        return result;
    }

    std::string AttackBundle::name() const{
        return "AttackBundle";
    }

} // namespace ecc
