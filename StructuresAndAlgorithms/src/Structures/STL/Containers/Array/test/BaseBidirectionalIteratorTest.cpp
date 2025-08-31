#include "Helpers/TestHelper.h"
#include "Structures/STL/Containers/Array/iterator/BaseBidirectionalIterator.h"
#include "Structures/STL/Containers/Array/iterator/BaseRandomAccessIterator.h"

using namespace Structures::STL;

template<typename IteratorType>
class BaseBidirectionalIteratorTest : public BaseTest { };

using BidirectionalIteratorTypes
    = testing::Types<BaseBidirectionalIterator<int>, BaseRandomAccessIterator<int>>;

TYPED_TEST_SUITE(BaseBidirectionalIteratorTest, BidirectionalIteratorTypes);

TYPED_TEST(BaseBidirectionalIteratorTest, decrement)
{
    constexpr int size = 10;
    int arr[size] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    BaseBidirectionalIterator<int> it(arr);
    const BaseBidirectionalIterator<int> begin(arr);

    ++it;
    EXPECT_NE(begin, it--);
    EXPECT_EQ(begin, it);

    ++it;
    EXPECT_EQ(begin, --it);
    EXPECT_EQ(begin, it);
}

TYPED_TEST(BaseBidirectionalIteratorTest, advance_decremental)
{
    constexpr int size = 10;
    int arr[size] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    BaseBidirectionalIterator<int> lIt(arr);
    BaseBidirectionalIterator<int> rIt(arr + size);

    std::advance(lIt, size / 2);
    std::advance(rIt, -size / 2);
    EXPECT_EQ(lIt, rIt);
}
