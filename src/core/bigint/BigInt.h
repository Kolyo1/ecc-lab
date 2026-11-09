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
    bool operator<(const BigInt&) const;
    BigInt modPow(const BigInt& e, const BigInt& m) const;
    BigInt modInverse(const BigInt& m) const;
    std::string toString(int base = 10) const;
    static void setBackend(std::shared_ptr<IBigIntBackend> prototype);
private:
    std::unique_ptr<IBigIntBackend> impl_;
};

} // namespace ecc
