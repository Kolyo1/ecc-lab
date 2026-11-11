#include "BigInt.h"
#include "BoostBackend.h"
#include <memory>
#include <utility>

namespace ecc {

std::shared_ptr<IBigIntBackend> BigInt::defaultBackend_ = nullptr;

BigInt::BigInt()
    : impl_(defaultBackend_ ? defaultBackend_->clone()
                            : std::unique_ptr<IBigIntBackend>(new BoostBackend())) {}

BigInt::BigInt(const std::string& s, int base)
    : impl_(defaultBackend_ ? defaultBackend_->clone()
                            : std::unique_ptr<IBigIntBackend>(new BoostBackend())) {
    impl_->fromString(s, base);
}

BigInt::BigInt(const BigInt& other) : impl_(other.impl_->clone()) {}
BigInt::BigInt(BigInt&& other) noexcept : impl_(std::move(other.impl_)) {}
BigInt& BigInt::operator=(const BigInt& other) {
    if (this != &other) impl_ = other.impl_->clone();
    return *this;
}
BigInt& BigInt::operator=(BigInt&& other) noexcept {
    if (this != &other) impl_ = std::move(other.impl_);
    return *this;
}

void BigInt::setBackend(std::shared_ptr<IBigIntBackend> prototype) {
    defaultBackend_ = prototype ? prototype->clone() : nullptr;
}

BigInt BigInt::operator+(const BigInt& rhs) const {
    BigInt r(*this);
    r.impl_->add(*rhs.impl_);
    return r;
}
BigInt BigInt::operator-(const BigInt& rhs) const {
    BigInt r(*this);
    r.impl_->sub(*rhs.impl_);
    return r;
}
BigInt BigInt::operator*(const BigInt& rhs) const {
    BigInt r(*this);
    r.impl_->mul(*rhs.impl_);
    return r;
}
BigInt BigInt::operator/(const BigInt& rhs) const {
    BigInt q, r;
    impl_->divmod(*rhs.impl_, *q.impl_, *r.impl_);
    return q;
}
BigInt BigInt::operator%(const BigInt& rhs) const {
    BigInt q, r;
    impl_->divmod(*rhs.impl_, *q.impl_, *r.impl_);
    return r;
}
bool BigInt::operator==(const BigInt& rhs) const { return impl_->compare(*rhs.impl_) == 0; }
bool BigInt::operator!=(const BigInt& rhs) const { return !(*this == rhs); }
bool BigInt::operator<(const BigInt& rhs) const  { return impl_->compare(*rhs.impl_) < 0; }
bool BigInt::operator>(const BigInt& rhs) const  { return rhs < *this; }
bool BigInt::operator<=(const BigInt& rhs) const { return !(rhs < *this); }
bool BigInt::operator>=(const BigInt& rhs) const { return !(*this < rhs); }

BigInt BigInt::modPow(const BigInt& e, const BigInt& m) const {
    BigInt r(*this);
    r.impl_->modPow(*e.impl_, *m.impl_);
    return r;
}
BigInt BigInt::modInverse(const BigInt& m) const {
    BigInt r(*this);
    r.impl_->modInverse(*m.impl_);
    return r;
}
std::string BigInt::toString(int base) const {
    return impl_->toString(base);
}

bool BigInt::testBit(std::size_t i) const {
    return impl_->testBit(i);
}

BigInt BigInt::operator>>(std::size_t n) const {
    BigInt r(*this);
    r.impl_->shiftRight(n);
    return r;
}

} // namespace ecc
