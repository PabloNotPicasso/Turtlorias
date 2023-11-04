#include "Helpers/TestHelper.h"
#include "Structures/STL/Containers/Array/Array.h"

using namespace Structures::STL;

class ArrayCreationTest : public BaseTest { };

TEST_F(ArrayCreationTest, creation)
{
    constexpr auto size = 10;
    const Array<int, size> array1;
    const Array<int, size> array2({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
    const Array<int, size> array3{0, 1, 2, 3, 4, 5};
}

TEST_F(ArrayCreationTest, empty)
{
    Array<int, 0> array;

    EXPECT_EQ(array.size(), 0);
    EXPECT_TRUE(array.empty());
    EXPECT_EQ(array.begin(), array.end());
    EXPECT_EQ(array.cbegin(), array.cend());
}

TEST_F(ArrayCreationTest, const_empty)
{
    const Array<int, 0> array;

    EXPECT_EQ(array.size(), 0);
    EXPECT_TRUE(array.empty());
    EXPECT_EQ(array.begin(), array.end());
    EXPECT_EQ(array.cbegin(), array.cend());
}

TEST_F(ArrayCreationTest, elementAccess)
{
    constexpr auto size = 5;
    const Array<int, size> array{0, 1, 2, 3, 4};

    for (size_t i = 0; i < size; ++i) {
        EXPECT_EQ(array[i], i);
        EXPECT_EQ(array.at(i), i);
        EXPECT_EQ(array.data()[i], i);
    }

    {
        int i = 0;
        for (const auto& element : array) {
            EXPECT_EQ(element, i);
            EXPECT_EQ(element, i);
            EXPECT_EQ(element, i);
            EXPECT_EQ(element, array[i]);
            EXPECT_EQ(element, array.at(i));
            EXPECT_EQ(element, array.data()[i]);
            ++i;
        }
    }

    EXPECT_EQ(array.back(), 4);
    EXPECT_EQ(array.back(), array[size - 1]);

    EXPECT_EQ(array.front(), 0);
    EXPECT_EQ(array.front(), array[0]);

    EXPECT_EQ(array.size(), size);
    EXPECT_FALSE(array.empty());
    EXPECT_NE(array.begin(), array.end());
    EXPECT_NE(array.cbegin(), array.cend());
}

TEST_F(ArrayCreationTest, compare)
{
    constexpr auto size = 5;
    const Array<int, size> array{0, 1, 2, 3, 4};
    Array<int, 0> empty;
    Array<int, size> notequal;
    Array<int, size> copy;
    copy = array;

    EXPECT_EQ(array, copy);
    EXPECT_NE(array, empty);
    EXPECT_NE(array, notequal);
}