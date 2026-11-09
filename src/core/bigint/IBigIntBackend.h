#pragma once
#include <string>
#include <memory>

namespace ecc {

class IBigIntBackend {
public:
    virtual ~IBigIntBackend() = default;
    virtual void fromString(const std::string& s, int base) = 0;
    virtual std::string toString(int base) const = 0;
    virtual std::unique_ptr<IBigIntBackend> clone() const = 0;
    virtual void add(const IBigIntBackend& rhs) = 0;
    virtual void sub(const IBigIntBackend& rhs) = 0;
    virtual void mul(const IBigIntBackend& rhs) = 0;
    virtual void divmod(const IBigIntBackend& d, IBigIntBackend& q, IBigIntBackend& r) const = 0;
    virtual void modPow(const IBigIntBackend& e, const IBigIntBackend& m) = 0;
    virtual void modInverse(const IBigIntBackend& m) = 0;
    virtual int  compare(const IBigIntBackend& rhs) const = 0;
};

} // namespace ecc
