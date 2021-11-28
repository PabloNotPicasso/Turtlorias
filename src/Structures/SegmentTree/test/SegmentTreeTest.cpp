#include "Structures/SegmentTree/SegmentTree.h"

#include <gtest/gtest.h>

#include <iostream>

using namespace Structures;

struct vec {
    int x, y;
    vec()
    {
    }
    vec(int x, int y)
        : x(x)
        , y(y)
    {
    }

    vec operator+(vec toAdd) const
    {
        return vec(x + toAdd.x, y + toAdd.y);
    }
};

template<
    typename ValueType,
    typename AccumulateFunction = std::function<ValueType(const ValueType&, const ValueType&)>>
ValueType funLinear(
    std::vector<ValueType> array, int l, int r, AccumulateFunction accum, ValueType zerro)
{
    ValueType accumulation = zerro;
    for (int i = l; i <= r; ++i)
        accumulation = accum(accumulation, array[i]);
    return accumulation;
}

TEST(SegmentTree, init)
{
    using ValueType = int;
    std::vector<ValueType> array = {1, 2, 3, 4, 5, 6, 7};

    SegmentTree<ValueType> segTree;
    EXPECT_FALSE(segTree.isBuilt());

    auto sum = [](const ValueType& a, const ValueType& b) { return a + b; };
    segTree.init(array, sum, 0);

    EXPECT_TRUE(segTree.isBuilt());
}

TEST(SegmentTree, getSum)
{
    using ValueType = int;
    std::vector<ValueType> array = {1, 2, 3, 4, 5, 6, 7};

    SegmentTree<ValueType> segTree;
    auto sum = [](const ValueType& a, const ValueType& b) { return a + b; };
    segTree.init(array, sum, 0);

    for (int l = 0; l < array.size(); ++l)
        for (int r = l; r < array.size(); ++r)
            EXPECT_EQ(funLinear<ValueType>(array, l, r, sum, 0), segTree.get(l, r));
}

TEST(SegmentTree, getProduct)
{
    using ValueType = int;
    std::vector<ValueType> array = {1, 2, 3, 4, 5, 6, 7};

    SegmentTree<ValueType> segTree;
    auto product = [](const ValueType& a, const ValueType& b) { return a * b; };
    segTree.init(array, product, 1);

    for (int l = 0; l < array.size(); ++l)
        for (int r = l; r < array.size(); ++r)
            EXPECT_EQ(funLinear<ValueType>(array, l, r, product, 1), segTree.get(l, r));
}

TEST(SegmentTree, getSumVec)
{
    using ValueType = vec;
    std::vector<ValueType> array = {{1, 1}, {14, -1}, {8, 5}, {5, 1}};

    SegmentTree<ValueType> segTree;
    auto sum = [](const ValueType& a, const ValueType& b) { return a + b; };
    segTree.init(array, sum, {0, 0});

    for (int l = 0; l < array.size(); ++l)
        for (int r = l; r < array.size(); ++r) {
            auto linear = funLinear<ValueType>(array, l, r, sum, {0, 0});
            auto ans = segTree.get(l, r);
            EXPECT_TRUE(linear.x == ans.x && linear.y == ans.y);
        }
}