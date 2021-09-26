#include "Structures/BoolVector/BoolVector.h"

#include <gtest/gtest.h>

using namespace Structures;

TEST(BoolVector, creation_empty)
{
    BoolVector bvector;
    EXPECT_EQ(bvector.capacity(), 8);
    EXPECT_EQ(bvector.size(), 0);
}

TEST(BoolVector, creation_nonempty)
{
    BoolVector bvector(7);
    EXPECT_EQ(bvector.capacity(), 8);
    EXPECT_EQ(bvector.size(), 7);
    for (size_t i = 0; i < bvector.size(); ++i) {
        EXPECT_EQ(bvector[i], 0);
    }
}

TEST(BoolVector, assign)
{
    BoolVector bvector(7);

    bvector[1] = bvector[5] = 1;
    EXPECT_EQ(bvector[1], 1);
    EXPECT_EQ(bvector[5], 1);

    EXPECT_EQ(bvector[0], 0);
    EXPECT_EQ(bvector[2], 0);
    EXPECT_EQ(bvector[3], 0);
    EXPECT_EQ(bvector[4], 0);
    EXPECT_EQ(bvector[6], 0);
}

TEST(BoolVector, push_back)
{
    BoolVector bvector;
    EXPECT_EQ(bvector.capacity(), 8);
    EXPECT_EQ(bvector.size(), 0);

    bvector.push_back(1);
    EXPECT_EQ(bvector.capacity(), 8);
    EXPECT_EQ(bvector.size(), 1);
    EXPECT_EQ(bvector[0], 1);

    bvector.push_back(0);
    EXPECT_EQ(bvector.capacity(), 8);
    EXPECT_EQ(bvector.size(), 2);
    EXPECT_EQ(bvector[1], 0);

    bvector.push_back(0);
    bvector.push_back(0);
    bvector.push_back(0);
    bvector.push_back(0);
    bvector.push_back(0);
    bvector.push_back(0);

    EXPECT_EQ(bvector.capacity(), 8);
    EXPECT_EQ(bvector.size(), 8);

    bvector.push_back(0);

    EXPECT_EQ(bvector.capacity(), 16);
    EXPECT_EQ(bvector.size(), 9);
}