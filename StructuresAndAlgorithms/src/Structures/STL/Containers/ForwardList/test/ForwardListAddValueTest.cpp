#include "Helpers/TestHelper.h"
#include "Structures/STL/Containers/ForwardList/ForwardList.h"

using namespace Structures::STL;

class ForwardListAddValueTest : public BaseTest { };

TEST_F(ForwardListAddValueTest, push_front_copy)
{
    Dummy dummy;
    ForwardList<Dummy> list;
    list.push_front(dummy);

    EXPECT_EQ(2, TestHelper::existingCopies);
    EXPECT_EQ(1, TestHelper::constructorCnt);
    EXPECT_EQ(0, TestHelper::destructorCnt);
    EXPECT_EQ(1, TestHelper::copyConstructorCnt);
    EXPECT_EQ(0, TestHelper::copyAssignCnt);
    EXPECT_EQ(0, TestHelper::moveConstructorCnt);
    EXPECT_EQ(0, TestHelper::moveAssignCnt);
}

TEST_F(ForwardListAddValueTest, push_front_move)
{
    Dummy dummy;
    ForwardList<Dummy> list;
    list.push_front(std::move(dummy));

    EXPECT_EQ(list.begin()->data, Dummy::initialDataString);
    EXPECT_EQ(dummy.data, "");

    EXPECT_EQ(2, TestHelper::existingCopies);
    EXPECT_EQ(1, TestHelper::constructorCnt);
    EXPECT_EQ(0, TestHelper::destructorCnt);
    EXPECT_EQ(0, TestHelper::copyConstructorCnt);
    EXPECT_EQ(0, TestHelper::copyAssignCnt);
    EXPECT_EQ(1, TestHelper::moveConstructorCnt);
    EXPECT_EQ(0, TestHelper::moveAssignCnt);
}

TEST_F(ForwardListAddValueTest, emplace_front)
{
    ForwardList<Dummy> list;

    const std::string myData = "MyData";

    list.emplace_front(myData);
    EXPECT_EQ(list.front().data, myData);

    EXPECT_EQ(1, TestHelper::existingCopies);
    EXPECT_EQ(1, TestHelper::constructorCnt);
    EXPECT_EQ(0, TestHelper::destructorCnt);
    EXPECT_EQ(0, TestHelper::copyConstructorCnt);
    EXPECT_EQ(0, TestHelper::copyAssignCnt);
    EXPECT_EQ(0, TestHelper::moveConstructorCnt);
    EXPECT_EQ(0, TestHelper::moveAssignCnt);

    list.emplace_front(myData);
    EXPECT_EQ(list.front().data, myData);

    EXPECT_EQ(2, TestHelper::existingCopies);
    EXPECT_EQ(2, TestHelper::constructorCnt);
    EXPECT_EQ(0, TestHelper::destructorCnt);
    EXPECT_EQ(0, TestHelper::copyConstructorCnt);
    EXPECT_EQ(0, TestHelper::copyAssignCnt);
    EXPECT_EQ(0, TestHelper::moveConstructorCnt);
    EXPECT_EQ(0, TestHelper::moveAssignCnt);
}

TEST_F(ForwardListAddValueTest, insert)
{
    ForwardList<int> list;
    auto toInsert = list.before_begin();
    toInsert = list.insertAfter(toInsert, 1);
    toInsert = list.insertAfter(toInsert, 2);
    toInsert = list.insertAfter(toInsert, 3);

    {
        int i = 1;
        for (auto element : list) {
            EXPECT_EQ(element, i);
            ++i;
        }
    }
    list.insertAfter(list.before_begin(), 0);

    {
        int i = 0;
        for (auto element : list) {
            EXPECT_EQ(element, i);
            ++i;
        }
    }

    auto iter = list.before_begin();
    ++(++iter);
    list.insertAfter(iter, 10);
    LOG_INF("4");
    ForwardList<int> expected({0, 1, 10, 2, 3});

    LOG_INF("5");
    EXPECT_EQ(list, expected);
}
