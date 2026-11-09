#pragma once
#include "IAttack.h"
#include <string>
#include <vector>
#include <functional>
#include <memory>

namespace ecc {

class AttackRegistry {
public:
    using Creator = std::function<std::unique_ptr<IAttack>()>;
    static AttackRegistry& instance();
    void registerAttack(const std::string& name, Creator c);
    std::vector<std::string> list() const;
private:
    AttackRegistry() = default;
};

} // namespace ecc
