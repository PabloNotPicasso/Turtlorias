#include "Helpers/TestHelper.h"
#include "Structures/STL/Containers/Array/iterator/BaseBidirectionalIterator.h"
#include "Structures/STL/Containers/Array/iterator/BaseForwardIterator.h"
#include "Structures/STL/Containers/Array/iterator/BaseInputIterator.h"
#include "Structures/STL/Containers/Array/iterator/BaseRandomAccessIterator.h"

using namespace Structures::STL;

template<typename IteratorType>
class BaseInputIteratorTest : public BaseTest { };

using InputIteratorTypes = testing::Types<
    BaseInputIterator<int>,
    BaseForwardIterator<int>,
    BaseBidirectionalIterator<int>,
    BaseRandomAccessIterator<int>>;

TYPED_TEST_SUITE(BaseInputIteratorTest, InputIteratorTypes);

TYPED_TEST(BaseInputIteratorTest, creation)
{
    int arr[10];
    BaseInputIterator<int> it1(arr);
    BaseInputIterator<int> copy(it1);
    BaseInputIterator<int> copyAssign;
    copyAssign = it1;

    EXPECT_EQ(it1, copy);
    EXPECT_EQ(it1, copyAssign);
    EXPECT_EQ(copy, copyAssign);
}

TYPED_TEST(BaseInputIteratorTest, equality_Check)
{
    int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    BaseInputIterator<int> it1(arr + 0);
    BaseInputIterator<int> it1_same(arr + 0);

    BaseInputIterator<int> it2(arr + 5);

    EXPECT_EQ(it1, it1_same);
    EXPECT_NE(it1, it2);

    EXPECT_EQ(it1, it1);
    EXPECT_EQ(it2, it2);
}
