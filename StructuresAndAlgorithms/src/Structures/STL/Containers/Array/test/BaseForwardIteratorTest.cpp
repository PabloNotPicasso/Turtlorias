#include "Helpers/TestHelper.h"
#include "Structures/STL/Containers/Array/iterator/BaseBidirectionalIterator.h"
#include "Structures/STL/Containers/Array/iterator/BaseForwardIterator.h"
#include "Structures/STL/Containers/Array/iterator/BaseRandomAccessIterator.h"

using namespace Structures::STL;

template<typename IteratorType>
class BaseForwardIteratorTest : public BaseTest {
};

using ForwardIteratorTypes = testing::
    Types<BaseForwardIterator<int>, BaseBidirectionalIterator<int>, BaseRandomAccessIterator<int>>;

TYPED_TEST_SUITE(BaseForwardIteratorTest, ForwardIteratorTypes);

TYPED_TEST(BaseForwardIteratorTest, increment)
{
    constexpr int size = 10;
    int arr[size] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    BaseForwardIterator<int> it1(arr);
    BaseForwardIterator<int> expected(arr);

    EXPECT_EQ(it1++, expected);
    EXPECT_EQ(it1, ++expected);

    auto it2 = it1;
    EXPECT_EQ(it1++, it2);
    EXPECT_EQ(it1, ++it2);

    EXPECT_NE(it1, expected);
    EXPECT_NE(it2, expected);
}

TYPED_TEST(BaseForwardIteratorTest, advance_incremental)
{
    constexpr int size = 10;
    int arr[size] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    BaseForwardIterator<int> it(arr);
    const BaseForwardIterator<int> mid(arr + size / 2);
    const BaseForwardIterator<int> end(arr + size);

    std::advance(it, size / 2);
    EXPECT_EQ(it, mid);

    std::advance(it, size / 2);
    EXPECT_EQ(it, end);
}