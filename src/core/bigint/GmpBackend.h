#pragma once
#include "IBigIntBackend.h"

namespace ecc {

class GmpBackend : public IBigIntBackend {
    // TODO: override all IBigIntBackend methods (GMP mpz_t)
};

} // namespace ecc
