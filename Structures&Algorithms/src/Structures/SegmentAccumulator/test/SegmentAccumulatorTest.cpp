#include "Structures/SegmentAccumulator/SegmentBrute/SegmentBrute.h"
#include "Structures/SegmentAccumulator/SegmentSqrt/SegmentSqrt.h"
#include "Structures/SegmentAccumulator/SegmentTree/SegmentTree.h"

#include "Helpers/Helpers.h"
#include <gtest/gtest.h>

using namespace Structures;
using namespace Helpers;

using Numeric = long long;

template<template <typename> typename TAccumulator, typename ValueType>
struct TestedClassContainer
{
    using _Acccumulator = TAccumulator<ValueType>;
    using _ValueType = ValueType;
};

template<typename TestedClassContainer>
class SegmentAccumulatorTest : public testing::Test {
protected:
    using _ValueType = typename TestedClassContainer::_ValueType;
    using _Acccumulator = typename TestedClassContainer::_Acccumulator;

    void SetUp() override{
        srand(time(nullptr));
        accumulator = new _Acccumulator();
    }

    void TearDown() override{
        delete accumulator;
    }

    std::vector<_ValueType> generateArray(int size)
    {
        return getRandomArray<_ValueType>(size);
    }

protected:
    ISegmentAccumulator<_ValueType>* accumulator;
};

// Setting implementations
using AccumulatorsImpl = testing::Types<
    TestedClassContainer<SegmentTree,Numeric>,
    TestedClassContainer<SegmentSqrt,Numeric>,
    TestedClassContainer<SegmentBrute,Numeric>,
    TestedClassContainer<SegmentTree,Vector>,
    TestedClassContainer<SegmentSqrt,Vector>,
    TestedClassContainer<SegmentBrute,Vector>>;

TYPED_TEST_SUITE(SegmentAccumulatorTest, AccumulatorsImpl);

// Tests
TYPED_TEST(SegmentAccumulatorTest, init)
{
    using ValueType = typename TypeParam::_ValueType;
    auto array = this->generateArray(10);

    EXPECT_FALSE(this->accumulator->isBuilt());

    auto sum = [](const ValueType& a, const ValueType& b) { return a + b; };
    this->accumulator->init(array, sum, 0);

    EXPECT_TRUE(this->accumulator->isBuilt());
}

TYPED_TEST(SegmentAccumulatorTest, getSum1e2)
{
    using ValueType = typename TypeParam::_ValueType;
    auto array = this->generateArray(1e2);

    auto sum = [](const ValueType& a, const ValueType& b) { return a + b; };
    this->accumulator->init(array, sum, 0);

    for (size_t l = 0; l < array.size(); ++l)
        for (size_t r = l; r < array.size(); ++r)
            EXPECT_EQ(linearAccumulation<ValueType>(array, l, r, sum, 0), this->accumulator->get(l, r));
}

TYPED_TEST(SegmentAccumulatorTest, getSum1e3)
{
    using ValueType = typename TypeParam::_ValueType;
    auto array = this->generateArray(1e3);

    auto sum = [](const ValueType& a, const ValueType& b) { return a + b; };
    this->accumulator->init(array, sum, 0);

    for (size_t l = 0; l < array.size(); ++l)
        for (size_t r = l; r < array.size(); ++r)
            EXPECT_EQ(linearAccumulation<ValueType>(array, l, r, sum, 0), this->accumulator->get(l, r));
}

TYPED_TEST(SegmentAccumulatorTest, getProduct)
{
    using ValueType = typename TypeParam::_ValueType;
    auto array = this->generateArray(10);

    auto product = [](const ValueType& a, const ValueType& b) { return a * b; };
    this->accumulator->init(array, product, 1);

    for (size_t l = 0; l < array.size(); ++l)
        for (size_t r = l; r < array.size(); ++r)
            EXPECT_EQ(linearAccumulation<ValueType>(array, l, r, product, 1), this->accumulator->get(l, r));
}

TYPED_TEST(SegmentAccumulatorTest, update)
{
    using ValueType = typename TypeParam::_ValueType;
    auto array = this->generateArray(50);
    auto sum = [](const ValueType& a, const ValueType& b) { return a + b; };
    auto zerro = 0ll;
    this->accumulator->init(array, sum, zerro);

    for( int i = 0; i < 100; ++i)
    {
        int id = getRandom<Numeric>(0,array.size()-1);
        Numeric newValue = getRandom<Numeric>(1,1e9);

        this->accumulator->update(id, newValue);
        array[id] = newValue;

        for (size_t l = 0; l < array.size(); ++l)
            for (size_t r = l; r < array.size(); ++r)
                EXPECT_EQ(linearAccumulation<ValueType>(array, l, r, sum, 0), this->accumulator->get(l, r));
    }
}