#include "Structures/STL/Containers/VectorBool/VectorBool.h"

#include <gtest/gtest.h>

using namespace Structures::STL;

TEST(VectorBoolTest, creation_empty)
{
    Vector<bool> bvector;
    EXPECT_EQ(bvector.capacity(), 8);
    EXPECT_EQ(bvector.size(), 0);
}

TEST(VectorBoolTest, creation_nonempty)
{
    Vector<bool> bvector(7);
    EXPECT_EQ(bvector.capacity(), 8);
    EXPECT_EQ(bvector.size(), 7);
    for (size_t i = 0; i < bvector.size(); ++i) {
        EXPECT_EQ(bvector[i], 0);
    }
}

TEST(VectorBoolTest, assign)
{
    Vector<bool> bvector(7);

    bvector[1] = bvector[5] = 1;
    EXPECT_EQ(bvector[1], 1);
    EXPECT_EQ(bvector[5], 1);

    EXPECT_EQ(bvector[0], 0);
    EXPECT_EQ(bvector[2], 0);
    EXPECT_EQ(bvector[3], 0);
    EXPECT_EQ(bvector[4], 0);
    EXPECT_EQ(bvector[6], 0);
}

TEST(VectorBoolTest, push_back)
{
    Vector<bool> bvector;
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

TEST(VectorBoolTest, copy)
{
    Vector<bool> bvector(7);
    bvector[1] = bvector[5] = 1;

    const Vector<bool> copy = bvector;

    EXPECT_EQ(copy[1], 1);
    EXPECT_EQ(copy[5], 1);
    EXPECT_EQ(copy[0], 0);
    EXPECT_EQ(copy[2], 0);
    EXPECT_EQ(copy[3], 0);
    EXPECT_EQ(copy[4], 0);
    EXPECT_EQ(copy[6], 0);

    // Should be compile error
    // copy[1] = 0;
}

TEST(VectorBoolTest, binaryOperators)
{
    Vector<bool> bvector(7);

    EXPECT_TRUE(
        ((!bvector[5] || bvector[0]) && (bvector[1] == bvector[2])) || (bvector[3] ^ bvector[4]));
}