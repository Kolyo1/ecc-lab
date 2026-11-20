#pragma once
#include "IAttack.h"
#include <string>
#include <vector>
#include <functional>
#include <memory>
#include <map>

namespace ecc {

class AttackRegistry {
public:
    using Creator = std::function<std::unique_ptr<IAttack>()>;
    static AttackRegistry& instance();
    void registerAttack(const std::string& name, Creator c);
    std::unique_ptr<IAttack> get(const std::string& name) const;
    std::vector<std::string> list() const;
private:
    AttackRegistry() = default;
    std::map<std::string, Creator> creators_;
};

} // namespace ecc
