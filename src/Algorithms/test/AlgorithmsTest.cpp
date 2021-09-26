#include "Algorithms/Algorithms.h"

#include <gtest/gtest.h>

using namespace Algorithm;

TEST(bin_pow, pow2_10)
{
    auto result = bin_pow(2, 10, 1000000);
    EXPECT_EQ(result, 1024);
}

TEST(bin_pow, pow2_10_mod2)
{
    auto result = bin_pow(2, 10, 2);
    EXPECT_EQ(result, 0);
}

TEST(bin_pow, pow2_10_mod10)
{
    auto result = bin_pow(2, 10, 10);
    EXPECT_EQ(result, 4);
}

TEST(disc_log, test)
{
    ll a = 5;
    ll b = 23;
    ll mod = 103;
    auto result = disc_log(a, b, mod);
    auto expect_b = bin_pow(a, result, mod);
    EXPECT_EQ(expect_b, b);
}