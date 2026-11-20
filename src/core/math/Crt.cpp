#include "Crt.h"

namespace ecc
{
    BigInt crt(const std::vector<BigInt>& residues, const std::vector<BigInt>& moduli){
        BigInt x = residues[0];
        BigInt M = moduli[0];

        for(std::size_t i = 1; i < residues.size(); ++i){
            BigInt r_i = residues[i];
            BigInt m_i = moduli[i];

            BigInt t = ((r_i - x) % m_i + m_i) % m_i;
            t = t * M.modInverse(m_i) % m_i;
            x = x + M * t;
            M = M * m_i;
        }
        return x % M;
    }
} // namespace ecc
