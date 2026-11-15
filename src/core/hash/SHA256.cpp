#include "Sha256.h"
#include <stdexcept>

namespace ecc {

Sha256::Sha256() {
    ctx_ = EVP_MD_CTX_new();
    if (!ctx_ || EVP_DigestInit_ex(ctx_, EVP_sha256(), nullptr) != 1)
        throw std::runtime_error("SHA-256 init failed");
}

Sha256::~Sha256() { EVP_MD_CTX_free(ctx_); }

void Sha256::update(const std::vector<unsigned char>& data) {
    EVP_DigestUpdate(ctx_, data.data(), data.size());
}

void Sha256::update(const std::string& s) {
    EVP_DigestUpdate(ctx_, s.data(), s.size());
}

std::vector<unsigned char> Sha256::finalize() {
    std::vector<unsigned char> out(32);
    unsigned int len = 0;
    EVP_DigestFinal_ex(ctx_, out.data(), &len);
    return out;
}

} // namespace ecc