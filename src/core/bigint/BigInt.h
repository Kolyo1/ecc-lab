#pragma once
#include "IBigIntBackend.h"
#include <memory>
#include <string>

namespace ecc {

class BigInt {
public:
    BigInt();
    explicit BigInt(const std::string& s, int base = 10);
    BigInt operator+(const BigInt&) const;
    BigInt operator-(const BigInt&) const;
    BigInt operator*(const BigInt&) const;
    BigInt operator/(const BigInt&) const;
    BigInt operator%(const BigInt&) const;
    bool operator==(const BigInt&) const;
    bool operator!=(const BigInt&) const;
    bool operator<(const BigInt&) const;
    bool operator>(const BigInt&) const;
    bool operator<=(const BigInt&) const;
    bool operator>=(const BigInt&) const;
    BigInt modPow(const BigInt& e, const BigInt& m) const;
    BigInt modInverse(const BigInt& m) const;
    std::string toString(int base = 10) const;
    static void setBackend(std::shared_ptr<IBigIntBackend> prototype);
    BigInt(const BigInt& other);
    BigInt(BigInt&& other) noexcept;
    BigInt& operator=(const BigInt& other);
    BigInt& operator=(BigInt&& other) noexcept;
    bool testBit(std::size_t i) const;
    BigInt operator>>(std::size_t n) const;
private:
    std::unique_ptr<IBigIntBackend> impl_;
    static std::shared_ptr<IBigIntBackend> defaultBackend_;
};

} // namespace ecc
