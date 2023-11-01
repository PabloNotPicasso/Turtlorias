#include "Structures/STL/Containers/List/List.h"
#include "TestHelper.h"

using namespace Structures::STL;

class ListAddValueTest : public ListTestBase { };

TEST_F(ListAddValueTest, push_back_copy)
{
    Dummy dummy;
    List<Dummy> list;
    list.push_back(dummy);

    EXPECT_EQ(list.size(), 1);

    EXPECT_EQ(2, TestHelper::existingCopies);
    EXPECT_EQ(1, TestHelper::constructorCnt);
    EXPECT_EQ(0, TestHelper::destructorCnt);
    EXPECT_EQ(1, TestHelper::copyConstructorCnt);
    EXPECT_EQ(0, TestHelper::copyAssignCnt);
    EXPECT_EQ(0, TestHelper::moveConstructorCnt);
    EXPECT_EQ(0, TestHelper::moveAssignCnt);
}

TEST_F(ListAddValueTest, push_back_move)
{
    Dummy dummy;
    List<Dummy> list;
    list.push_back(std::move(dummy));

    EXPECT_EQ(list.size(), 1);

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

TEST_F(ListAddValueTest, emplace_back)
{
    List<Dummy> list;

    const std::string myData = "MyData";

    list.emplace_back(myData);
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.back().data, myData);

    EXPECT_EQ(1, TestHelper::existingCopies);
    EXPECT_EQ(1, TestHelper::constructorCnt);
    EXPECT_EQ(0, TestHelper::destructorCnt);
    EXPECT_EQ(0, TestHelper::copyConstructorCnt);
    EXPECT_EQ(0, TestHelper::copyAssignCnt);
    EXPECT_EQ(0, TestHelper::moveConstructorCnt);
    EXPECT_EQ(0, TestHelper::moveAssignCnt);

    list.emplace_back(myData);
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.back().data, myData);

    EXPECT_EQ(2, TestHelper::existingCopies);
    EXPECT_EQ(2, TestHelper::constructorCnt);
    EXPECT_EQ(0, TestHelper::destructorCnt);
    EXPECT_EQ(0, TestHelper::copyConstructorCnt);
    EXPECT_EQ(0, TestHelper::copyAssignCnt);
    EXPECT_EQ(0, TestHelper::moveConstructorCnt);
    EXPECT_EQ(0, TestHelper::moveAssignCnt);
}

TEST_F(ListAddValueTest, insert)
{
    List<int> list;
    list.insert(list.end(), 1);
    list.insert(list.end(), 2);
    list.insert(list.end(), 3);

    {
        int i = 1;
        for (auto element : list) {
            EXPECT_EQ(element, i);
            ++i;
        }
    }
    list.insert(list.begin(), 0);

    {
        int i = 0;
        for (auto element : list) {
            EXPECT_EQ(element, i);
            ++i;
        }
    }

    auto iter = list.begin();
    ++(++iter);
    list.insert(iter, 10);
    List<int> expected({0, 1, 10, 2, 3});

    EXPECT_EQ(list, expected);
}