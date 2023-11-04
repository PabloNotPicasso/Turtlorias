#include "Helpers/TestHelper.h"
#include "Structures/STL/Containers/Array/iterator/BaseRandomAccessIterator.h"

using namespace Structures::STL;

template<typename IteratorType>
class BaseRandomAccessIteratorTest : public BaseTest {
};

using RandomAccessIteratorTypes = testing::Types<BaseRandomAccessIterator<int>>;

TYPED_TEST_SUITE(BaseRandomAccessIteratorTest, RandomAccessIteratorTypes);

TYPED_TEST(BaseRandomAccessIteratorTest, integer_sum)
{
    constexpr int size = 10;
    int arr[size] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    const BaseRandomAccessIterator<int> begin(arr);
    const BaseRandomAccessIterator<int> mid(arr + size / 2);
    const BaseRandomAccessIterator<int> end(arr + size);

    EXPECT_EQ(begin + size / 2, end - size / 2);
    EXPECT_EQ(begin + size / 2, mid);
    EXPECT_EQ(mid, end - size / 2);

    EXPECT_EQ(begin + size, end);
    EXPECT_EQ(end - size, begin);
    EXPECT_EQ(end - begin, size);
}

TYPED_TEST(BaseRandomAccessIteratorTest, greater_less)
{
    constexpr int size = 10;
    int arr[size] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    const BaseRandomAccessIterator<int> begin(arr);
    const BaseRandomAccessIterator<int> mid(arr + size / 2);
    const BaseRandomAccessIterator<int> end(arr + size);

    EXPECT_TRUE(begin < mid);
    EXPECT_TRUE(begin < end);
    EXPECT_TRUE(begin <= begin);
    EXPECT_TRUE(begin >= begin);

    EXPECT_TRUE(begin + size > mid);
}