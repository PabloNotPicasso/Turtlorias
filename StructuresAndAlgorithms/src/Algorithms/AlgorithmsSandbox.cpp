#include "AlgorithmsSandbox.h"

#include <bits/stdc++.h>
using namespace std;

namespace Algorithm {

// Binary Power O(log n)
// x = a^pw (mod mod)
ll bin_pow(ll a, ll pw, ll mod)
{
    ll res = 1;
    while (pw) {
        if (pw & 1)
            (res *= a) %= mod;
        (a *= a) %= mod;
        pw >>= 1;
    }
    return res;
}

// Discrete logarithm. Baby-step giant-step
// Find x if a^x = b (mod mod) mod is prime
ll disc_log(ll a, ll b, ll mod)
{
    // x = np - q
    ll p = 0, q = 0;
    ll n = sqrt(mod) + 1;

    ll a_pow_n = bin_pow(a, n, mod);
    ll cur_pow = a_pow_n;
    map<ll, ll> mod_pow;
    for (int i = 1; i <= n; ++i) {
        ll pwr = n * i;
        ll pwrMod = cur_pow;
        (cur_pow *= a_pow_n) %= mod;
        mod_pow[pwrMod] = i;
    }
    for (int i = 0; !q && i < n; ++i) {
        ll pwr = i;
        ll pwrMod = (b * bin_pow(a, pwr, mod)) % mod;
        if (mod_pow.count(pwrMod)) {
            p = mod_pow[pwrMod];
            q = i;
        }
    }
    return n * p - q;
}

} // namespace Algorithm
