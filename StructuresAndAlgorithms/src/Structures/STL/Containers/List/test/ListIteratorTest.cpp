#include "Structures/STL/Containers/List/List.h"
#include "TestHelper.h"

using namespace Structures::STL;

class ListIteratorTest : public ListTestBase { };

TEST_F(ListIteratorTest, emptyList)
{
    List<Dummy> emptyList;

    EXPECT_EQ(emptyList.size(), 0);
    EXPECT_EQ(emptyList.begin(), emptyList.end());
    EXPECT_EQ(emptyList.cbegin(), emptyList.cend());
}

TEST_F(ListIteratorTest, increment)
{
    constexpr auto size = 5;
    List<int> list(size, 0);

    auto it = list.begin();

    EXPECT_EQ(it++, list.begin());
    EXPECT_EQ(it, ++list.begin());

    auto secondElementIt = it;
    EXPECT_EQ(it++, secondElementIt);
    EXPECT_EQ(it, ++secondElementIt);

    EXPECT_NE(it, list.begin());
    EXPECT_NE(secondElementIt, list.begin());
}

TEST_F(ListIteratorTest, decrement)
{
    constexpr auto size = 5;
    List<int> list(size, 0);

    auto firstElementIt = list.begin();
    auto secondElementIt = std::next(firstElementIt);

    EXPECT_NE(firstElementIt, secondElementIt--);
    EXPECT_EQ(firstElementIt, secondElementIt);
    ++secondElementIt;

    EXPECT_EQ(firstElementIt, --secondElementIt);
    EXPECT_EQ(firstElementIt, secondElementIt);
}

TEST_F(ListIteratorTest, advance)
{
    constexpr auto size = 5;
    List<int> list(size, 0);
    auto lIt = list.begin();
    auto rIt = list.end();
    std::advance(lIt, 2);
    std::advance(rIt, -3);

    EXPECT_EQ(lIt, rIt);
}