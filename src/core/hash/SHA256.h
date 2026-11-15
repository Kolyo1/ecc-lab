#pragma once
#include "IHash.h"
#include <openssl/evp.h>

namespace ecc {

class Sha256 : public IHash {
public:
    Sha256();
    ~Sha256();
    void update(const std::vector<unsigned char>& data) override;
    void update(const std::string& s) override;
    std::vector<unsigned char> finalize() override;
    std::size_t digestSize() const override { return 32; }
private:
    EVP_MD_CTX* ctx_;
};

} // namespace ecc