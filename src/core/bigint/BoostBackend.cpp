#include "BoostBackend.h"
#include <boost/multiprecision/cpp_int.hpp>
#include <stdexcept>
#include <sstream>
#include <algorithm>

namespace ecc {

BoostBackend::BoostBackend(const std::string& s, int base) {
    fromString(s, base);
}

void BoostBackend::fromString(const std::string& s, int base) {
    if (base == 10) {
        value_ = boost::multiprecision::cpp_int(s);
    } else if (base == 16) {
        std::string hex = s;
        if (hex.rfind("0x", 0) == 0 || hex.rfind("0X", 0) == 0)
            hex = hex.substr(2);
        value_ = boost::multiprecision::cpp_int("0x" + hex);
    } else if (base == 2) {
        boost::multiprecision::cpp_int v = 0;
        for (char c : s) {
            if (c == '0' || c == '1') {
                v <<= 1;
                if (c == '1') v |= 1;
            } else if (c == ' ' || c == '\'') {
                continue;
            } else {
                throw std::invalid_argument("invalid binary digit");
            }
        }
        value_ = v;
    } else {
        throw std::invalid_argument("unsupported base");
    }
}

std::string BoostBackend::toString(int base) const {
    if (base == 10) {
        return value_.str();
    } else if (base == 16) {
        std::ostringstream oss;
        oss << std::hex << value_;
        return oss.str();
    } else if (base == 2) {
        if (value_ == 0) return "0";
        std::string bits;
        auto v = value_;
        while (v > 0) {
            bits.push_back((v & 1) ? '1' : '0');
            v >>= 1;
        }
        std::reverse(bits.begin(), bits.end());
        return bits;
    }
    throw std::invalid_argument("unsupported base");
}

std::unique_ptr<IBigIntBackend> BoostBackend::clone() const {
    return std::make_unique<BoostBackend>(*this);
}

void BoostBackend::add(const IBigIntBackend& rhs) {
    const auto& other = dynamic_cast<const BoostBackend&>(rhs);
    value_ += other.value_;
}

void BoostBackend::sub(const IBigIntBackend& rhs) {
    const auto& other = dynamic_cast<const BoostBackend&>(rhs);
    value_ -= other.value_;
}

void BoostBackend::mul(const IBigIntBackend& rhs) {
    const auto& other = dynamic_cast<const BoostBackend&>(rhs);
    value_ *= other.value_;
}

void BoostBackend::divmod(const IBigIntBackend& d, IBigIntBackend& q, IBigIntBackend& r) const {
    const auto& dd = dynamic_cast<const BoostBackend&>(d);
    auto& qq = dynamic_cast<BoostBackend&>(q);
    auto& rr = dynamic_cast<BoostBackend&>(r);
    qq.value_ = value_ / dd.value_;
    rr.value_ = value_ % dd.value_;
}

void BoostBackend::modPow(const IBigIntBackend& e, const IBigIntBackend& m) {
    const auto& ee = dynamic_cast<const BoostBackend&>(e);
    const auto& mm = dynamic_cast<const BoostBackend&>(m);
    boost::multiprecision::cpp_int result = 1;
    boost::multiprecision::cpp_int base = value_ % mm.value_;
    boost::multiprecision::cpp_int exp = ee.value_;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % mm.value_;
        base = (base * base) % mm.value_;
        exp >>= 1;
    }
    value_ = result;
}

void BoostBackend::modInverse(const IBigIntBackend& m) {
    const auto& mm = dynamic_cast<const BoostBackend&>(m);
    boost::multiprecision::cpp_int old_r = value_;
    boost::multiprecision::cpp_int r = mm.value_;
    boost::multiprecision::cpp_int old_s = 1;
    boost::multiprecision::cpp_int s = 0;
    while (r != 0) {
        boost::multiprecision::cpp_int q = old_r / r;
        boost::multiprecision::cpp_int tmp_r = r;
        r = old_r - q * r;
        old_r = tmp_r;
        boost::multiprecision::cpp_int tmp_s = s;
        s = old_s - q * s;
        old_s = tmp_s;
    }
    if (old_r != 1) throw std::runtime_error("no modular inverse");
    boost::multiprecision::cpp_int inv = old_s % mm.value_;
    if (inv < 0) inv += mm.value_;
    value_ = inv;
}

int BoostBackend::compare(const IBigIntBackend& rhs) const {
    const auto& other = dynamic_cast<const BoostBackend&>(rhs);
    if (value_ < other.value_) return -1;
    if (value_ > other.value_) return 1;
    return 0;
}

} // namespace ecc
