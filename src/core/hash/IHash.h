#pragma once
#include <string>
#include <vector>

namespace ecc {

class IHash {
public:
    virtual ~IHash() = default;
    virtual void update(const std::vector<unsigned char>& data) = 0;
    virtual void update(const std::string& s) = 0;
    virtual std::vector<unsigned char> finalize() = 0;
    virtual std::size_t digestSize() const = 0;
};

} // namespace ecc