#pragma once
typedef long long ll;

namespace Algorithm {

// Binary Power O(log n)
// x = a^pw (mod mod)
ll bin_pow(ll a, ll pw, ll mod);

// Discrete logarithm. Baby-step giant-step
// Find x if a^x = b (mod mod) mod is prime
ll disc_log(ll a, ll b, ll mod);

} // namespace Algorithm
