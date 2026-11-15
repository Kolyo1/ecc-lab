#include "CurveRegistry.h"

namespace ecc {
    CurveRegistry& CurveRegistry::instance(){
        static CurveRegistry reg;
        return reg;
    }

    void CurveRegistry::registerCurve(const std::string& name, Creator c){
        creators_[name] = std::move(c);
    }

    std::unique_ptr<ICurve> CurveRegistry::get(const std::string& name) const {
        auto it = creators_.find(name);
        if(it == creators_.end()) return nullptr;
        return it->second();
    }

    std::vector<std::string> CurveRegistry::list() const{
        std::vector<std::string> name;
        name.reserve(creators_.size());
        for(const auto& r : creators_) name.push_back(r.first);
        return name;
    }
} // namespace ecc
