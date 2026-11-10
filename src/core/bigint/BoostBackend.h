#pragma once
#include "IBigIntBackend.h"
#include <boost/multiprecision/cpp_int.hpp>
#include <memory>
#include <string>

namespace ecc {

class BoostBackend : public IBigIntBackend {
public:
    BoostBackend() = default;
    explicit BoostBackend(const std::string& s, int base);
    BoostBackend(const BoostBackend&) = default;
    void fromString(const std::string& s, int base) override;
    std::string toString(int base) const override;
    std::unique_ptr<IBigIntBackend> clone() const override;
    void add(const IBigIntBackend& rhs) override;
    void sub(const IBigIntBackend& rhs) override;
    void mul(const IBigIntBackend& rhs) override;
    void divmod(const IBigIntBackend& d, IBigIntBackend& q, IBigIntBackend& r) const override;
    void modPow(const IBigIntBackend& e, const IBigIntBackend& m) override;
    void modInverse(const IBigIntBackend& m) override;
    int compare(const IBigIntBackend& rhs) const override;
private:
    boost::multiprecision::cpp_int value_ = 0;
};

} // namespace ecc
