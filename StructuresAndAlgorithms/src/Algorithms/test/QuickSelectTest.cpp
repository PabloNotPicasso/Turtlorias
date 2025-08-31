#include "Algorithms/QuickSelectT.h"

#include <gtest/gtest.h>

#include <random>
#include <vector>

using namespace Algorithm;

TEST(quick_select, test_less)
{
    std::vector<int> v{5, 4, 3, 2, 1};
    int k = 4;
    auto result = quick_select(v.begin(), v.end(), k);
    EXPECT_EQ(*result, 5);
}

TEST(quick_select, test_greater)
{
    std::vector<int> v{5, 4, 3, 2, 1};
    int k = 4;
    auto result = quick_select(v.begin(), v.end(), k, std::greater<int>());
    EXPECT_EQ(*result, 1);
}

TEST(quick_select, test_less_random)
{
    const int vectorSize = 1000;
    const int trials = 1000;
    std::vector<int> v(vectorSize);

    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> val_dist(0, 1'000'000);
    std::uniform_int_distribution<int> idx_dist(0, vectorSize - 1);

    for (int test_id = 0; test_id < trials; ++test_id) {
        int k = idx_dist(rng);
        for (int i = 0; i < vectorSize; ++i) {
            v[i] = val_dist(rng);
        }
        std::vector<int> copyVector(v);
        sort(copyVector.begin(), copyVector.end(), std::less<int>());

        auto result = quick_select(v.begin(), v.end(), k, std::less<int>());
        EXPECT_EQ(*result, copyVector[k]);
    }
}

TEST(quick_select, test_greater_random)
{
    const int vectorSize = 1000;
    const int trials = 1000;
    std::vector<int> v(vectorSize);

    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> val_dist(0, 1'000'000);
    std::uniform_int_distribution<int> idx_dist(0, vectorSize - 1);

    for (int test_id = 0; test_id < trials; ++test_id) {
        int k = idx_dist(rng);
        for (int i = 0; i < vectorSize; ++i) {
            v[i] = val_dist(rng);
        }
        std::vector<int> copyVector(v);
        sort(copyVector.begin(), copyVector.end(), std::greater<int>());

        auto result = quick_select(v.begin(), v.end(), k, std::greater<int>());
        EXPECT_EQ(*result, copyVector[k]);
    }
}
