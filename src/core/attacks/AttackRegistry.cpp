#include "AttackRegistry.h"

namespace ecc {

    AttackRegistry& AttackRegistry::instance(){
        static AttackRegistry reg;
        return reg;
    }

    void AttackRegistry::registerAttack(const std::string& name, Creator c){
        creators_[name] = std::move(c);
    }

    std::unique_ptr<IAttack> AttackRegistry::get(const std::string& name) const{
        auto it = creators_.find(name);
        if(it == creators_.end()) return nullptr;
        return it->second();
    }

    std::vector<std::string> AttackRegistry::list() const{
        std::vector<std::string> names;
        for(const auto& kv : creators_) names.push_back(kv.first);
        return names;
    }

} // namespace ecc
