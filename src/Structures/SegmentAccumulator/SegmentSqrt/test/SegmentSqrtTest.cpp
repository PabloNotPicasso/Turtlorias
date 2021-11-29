#include "Structures/SegmentAccumulator/SegmentSqrt/SegmentSqrt.h"

#include <gtest/gtest.h>

#include <iostream>

using namespace Structures;

struct vec {
    int x, y;
    vec() = default;
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

TEST(SegmentSqrt, init)
{
    using ValueType = int;
    std::vector<ValueType> array = {1, 2, 3, 4, 5, 6, 7};

    SegmentSqrt<ValueType> segmentSqrt;
    EXPECT_FALSE(segmentSqrt.isBuilt());

    auto sum = [](const ValueType& a, const ValueType& b) { return a + b; };
    segmentSqrt.init(array, sum, 0);

    EXPECT_TRUE(segmentSqrt.isBuilt());
}

TEST(SegmentSqrt, getSum)
{
    using ValueType = int;
    std::vector<ValueType> array = {1, 2, 3, 4, 5, 6, 7};

    SegmentSqrt<ValueType> segmentSqrt;
    auto sum = [](const ValueType& a, const ValueType& b) { return a + b; };
    segmentSqrt.init(array, sum, 0);

    for (size_t l = 0; l < array.size(); ++l)
        for (size_t r = l; r < array.size(); ++r)
            EXPECT_EQ(funLinear<ValueType>(array, l, r, sum, 0), segmentSqrt.get(l, r));
}

TEST(SegmentSqrt, getProduct)
{
    using ValueType = int;
    std::vector<ValueType> array = {1, 2, 3, 4, 5, 6, 7};

    SegmentSqrt<ValueType> segmentSqrt;
    auto product = [](const ValueType& a, const ValueType& b) { return a * b; };
    segmentSqrt.init(array, product, 1);

    for (size_t l = 0; l < array.size(); ++l)
        for (size_t r = l; r < array.size(); ++r)
            EXPECT_EQ(funLinear<ValueType>(array, l, r, product, 1), segmentSqrt.get(l, r));
}

TEST(SegmentSqrt, getSumVec)
{
    using ValueType = vec;
    std::vector<ValueType> array = {{1, 1}, {14, -1}, {8, 5}, {5, 1}};

    SegmentSqrt<ValueType> segmentSqrt;
    auto sum = [](const ValueType& a, const ValueType& b) { return a + b; };
    segmentSqrt.init(array, sum, {0, 0});

    for (size_t l = 0; l < array.size(); ++l)
        for (size_t r = l; r < array.size(); ++r) {
            auto linear = funLinear<ValueType>(array, l, r, sum, {0, 0});
            auto ans = segmentSqrt.get(l, r);
            EXPECT_TRUE(linear.x == ans.x && linear.y == ans.y);
        }
}