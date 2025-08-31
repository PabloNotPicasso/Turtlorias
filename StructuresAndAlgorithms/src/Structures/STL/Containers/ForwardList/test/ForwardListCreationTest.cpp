#include "Helpers/TestHelper.h"
#include "Structures/STL/Containers/ForwardList/ForwardList.h"

using namespace Structures::STL;

class ForwardListCreationTest : public BaseTest { };

TEST_F(ForwardListCreationTest, empty)
{
    ForwardList<Dummy> list;

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

TEST_F(ForwardListCreationTest, sizeConstructing)
{
    constexpr size_t size = 10;
    ForwardList<Dummy> list(size);

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

TEST_F(ForwardListCreationTest, sizeConstructing_zero)
{
    constexpr size_t size = 0;
    ForwardList<Dummy> list(size);

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

TEST_F(ForwardListCreationTest, copyCountConstructing)
{
    Dummy dummy;
    dummy.data = "SomeOtherData";
    constexpr size_t createdForTestCnt = 1;

    constexpr size_t newSize = 10;
    ForwardList<Dummy> list(newSize, dummy);

    for (auto it = list.begin(); it != list.end(); ++it) {
        EXPECT_EQ(it->data, dummy.data);
    }

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

TEST_F(ForwardListCreationTest, copyOtherForwardList)
{
    Dummy dummy;
    dummy.data = "SomeOtherData";
    constexpr size_t createdForTestCnt = 1;
    constexpr size_t newSize = 10;
    ForwardList<Dummy> list(newSize, dummy);
    TestHelper::reset();
}
