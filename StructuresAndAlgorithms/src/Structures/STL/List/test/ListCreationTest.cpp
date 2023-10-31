#include "Structures/STL/List/List.h"
#include "TestHelper.h"

using namespace Structures::STL;

class ListCreationTest : public ListTestBase { };

TEST_F(ListCreationTest, empty)
{
    List<Dummy> list;

    EXPECT_EQ(list.size(), 0);
    EXPECT_EQ(list.begin(), list.end());
    EXPECT_TRUE(list.empty());

    EXPECT_EQ(0, TestHelper::existingCopies);
    EXPECT_EQ(0, TestHelper::constructorCnt);
    EXPECT_EQ(0, TestHelper::destructorCnt);
    EXPECT_EQ(0, TestHelper::copyConstructorCnt);
    EXPECT_EQ(0, TestHelper::copyAssignCnt);
    EXPECT_EQ(0, TestHelper::moveConstructorCnt);
    EXPECT_EQ(0, TestHelper::moveAssignCnt);
}

TEST_F(ListCreationTest, sizeConstructing)
{
    constexpr size_t size = 10;
    List<Dummy> list(size);

    EXPECT_EQ(list.size(), size);
    EXPECT_NE(list.begin(), list.end());
    EXPECT_FALSE(list.empty());

    for (auto it = list.begin(); it != list.end(); ++it) {
        EXPECT_EQ(it->data, Dummy::initialDataString);
    }

    EXPECT_EQ(size, TestHelper::existingCopies);
    EXPECT_EQ(size, TestHelper::constructorCnt);
    EXPECT_EQ(0, TestHelper::destructorCnt);
    EXPECT_EQ(0, TestHelper::copyConstructorCnt);
    EXPECT_EQ(0, TestHelper::copyAssignCnt);
    EXPECT_EQ(0, TestHelper::moveConstructorCnt);
    EXPECT_EQ(0, TestHelper::moveAssignCnt);
}

TEST_F(ListCreationTest, sizeConstructing_zero)
{
    constexpr size_t size = 0;
    List<Dummy> list(size);

    EXPECT_EQ(list.size(), size);
    EXPECT_EQ(list.begin(), list.end());
    EXPECT_TRUE(list.empty());

    for (auto it = list.begin(); it != list.end(); ++it) {
        EXPECT_EQ(it->data, Dummy::initialDataString);
    }

    EXPECT_EQ(size, TestHelper::existingCopies);
    EXPECT_EQ(size, TestHelper::constructorCnt);
    EXPECT_EQ(0, TestHelper::destructorCnt);
    EXPECT_EQ(0, TestHelper::copyConstructorCnt);
    EXPECT_EQ(0, TestHelper::copyAssignCnt);
    EXPECT_EQ(0, TestHelper::moveConstructorCnt);
    EXPECT_EQ(0, TestHelper::moveAssignCnt);
}

TEST_F(ListCreationTest, copyCountConstructing)
{
    Dummy dummy;
    dummy.data = "SomeOtherData";
    constexpr size_t createdForTestCnt = 1;

    constexpr size_t newSize = 10;
    List<Dummy> list(newSize, dummy);

    for (auto it = list.begin(); it != list.end(); ++it) {
        EXPECT_EQ(it->data, dummy.data);
    }

    EXPECT_EQ(list.size(), newSize);
    EXPECT_NE(list.begin(), list.end());
    EXPECT_FALSE(list.empty());

    EXPECT_EQ(createdForTestCnt + newSize, TestHelper::existingCopies);
    EXPECT_EQ(createdForTestCnt, TestHelper::constructorCnt);
    EXPECT_EQ(0, TestHelper::destructorCnt);
    EXPECT_EQ(newSize, TestHelper::copyConstructorCnt);
    EXPECT_EQ(0, TestHelper::copyAssignCnt);
    EXPECT_EQ(0, TestHelper::moveConstructorCnt);
    EXPECT_EQ(0, TestHelper::moveAssignCnt);
}

TEST_F(ListCreationTest, copyOtherList)
{
    Dummy dummy;
    dummy.data = "SomeOtherData";
    constexpr size_t createdForTestCnt = 1;
    constexpr size_t newSize = 10;
    List<Dummy> list(newSize, dummy);
    TestHelper::reset();
}