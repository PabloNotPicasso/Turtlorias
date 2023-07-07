#pragma once

#include <stddef.h>

#include <cstdint>

namespace Algorithm {

// Binary Power O(log n)
// x = a^pw (mod mod)
template<typename T>
T bin_pow(T a, size_t pw, int64_t mod)
{
    T res = 1;
    while (pw) {
        if (pw & 1)
            (res *= a) %= mod;
        (a *= a) %= mod;
        pw >>= 1;
    }
    return res;
}

} // namespace Algorithm