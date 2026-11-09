#pragma once
#include "IDefense.h"
#include <vector>
#include <memory>
#include <string>

namespace ecc {

class Defender {
public:
    void addDefense(std::shared_ptr<IDefense> d);
    void enable(const std::string& name);
    void disable(const std::string& name);
private:
    std::vector<std::shared_ptr<IDefense>> defenses_;
};

} // namespace ecc
