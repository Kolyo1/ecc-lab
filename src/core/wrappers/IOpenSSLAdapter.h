#pragma once
#include "../bigint/BigInt.h"
#include <vector>
#include <string>

namespace ecc {

class IOpenSSLAdapter {
public:
    virtual ~IOpenSSLAdapter() = default;
    virtual std::vector<unsigned char> ecdh(const std::string& curveName, const BigInt& priv, const std::vector<unsigned char>& peerPub) = 0;
    virtual std::vector<unsigned char> ecdsaSign(const std::string& curveName, const BigInt& priv, const std::vector<unsigned char>& msg) = 0;
    virtual bool ecdsaVerify(const std::string& curveName, const std::vector<unsigned char>& pub, const std::vector<unsigned char>& msg, const std::vector<unsigned char>& sig) = 0;
};

} // namespace ecc
