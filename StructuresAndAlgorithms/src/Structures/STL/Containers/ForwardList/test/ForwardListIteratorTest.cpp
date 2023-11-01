#include "Structures/STL/Containers/ForwardList/ForwardList.h"
#include "TestHelper.h"

using namespace Structures::STL;

class ForwardListIteratorTest : public TestBase { };

TEST_F(ForwardListIteratorTest, emptyForwardList)
{
    ForwardList<Dummy> emptyForwardList;

    EXPECT_EQ(emptyForwardList.begin(), emptyForwardList.end());
    EXPECT_EQ(emptyForwardList.cbegin(), emptyForwardList.cend());
}

TEST_F(ForwardListIteratorTest, increment)
{
    constexpr auto size = 5;
    ForwardList<int> list(size, 0);

    auto it = list.begin();

    EXPECT_EQ(it++, list.begin());
    EXPECT_EQ(it, ++list.begin());

    auto secondElementIt = it;
    EXPECT_EQ(it++, secondElementIt);
    EXPECT_EQ(it, ++secondElementIt);

    EXPECT_NE(it, list.begin());
    EXPECT_NE(secondElementIt, list.begin());
}

TEST_F(ForwardListIteratorTest, advance)
{
    constexpr auto size = 5;
    ForwardList<int> list(size, 0);
    auto lIt = list.begin();
    auto rIt = list.end();
    std::advance(lIt, 5);

    EXPECT_EQ(lIt, rIt);
}