#pragma once
#include <vector>
#include <cstddef>
#include "core/bigint/BigInt.h"

namespace ecc{

    class IRandom{
        public:
            virtual ~IRandom () = default;
            virtual std::vector<unsigned char> randomBytes(std::size_t n)  = 0;
            virtual BigInt inRange(const BigInt& low, const BigInt& high) = 0;
    };

}