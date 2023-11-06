#include "Helpers/TestHelper.h"
#include "Structures/STL/Containers/Deque/Deque.h"

using namespace Structures::STL;

class DequeTest : public BaseTest { };

TEST_F(DequeTest, creation_empty)
{
    Deque<Dummy> deque;

    EXPECT_EQ(deque.size(), 0);

    EXPECT_EQ(0, TestHelper::existingCopies);
    EXPECT_EQ(0, TestHelper::constructorCnt);
    EXPECT_EQ(0, TestHelper::destructorCnt);
    EXPECT_EQ(0, TestHelper::copyConstructorCnt);
    EXPECT_EQ(0, TestHelper::copyAssignCnt);
    EXPECT_EQ(0, TestHelper::moveConstructorCnt);
    EXPECT_EQ(0, TestHelper::moveAssignCnt);
}

TEST_F(DequeTest, creation_constructing)
{
    size_t size = 10;
    Deque<Dummy> deque(size);

    EXPECT_EQ(deque.size(), size);

    for (size_t i = 0; i < deque.size(); ++i) {
        EXPECT_EQ(deque[i].data, Dummy::initialDataString);
        EXPECT_EQ(deque.at(i).data, Dummy::initialDataString);
    }

    EXPECT_EQ(10, TestHelper::existingCopies);
    EXPECT_EQ(10, TestHelper::constructorCnt);
    EXPECT_EQ(0, TestHelper::destructorCnt);
    EXPECT_EQ(0, TestHelper::copyConstructorCnt);
    EXPECT_EQ(0, TestHelper::copyAssignCnt);
    EXPECT_EQ(0, TestHelper::moveConstructorCnt);
    EXPECT_EQ(0, TestHelper::moveAssignCnt);
}

TEST_F(DequeTest, creation_copy)
{
    Dummy dummy;
    dummy.data = "SomeOtherData";
    size_t newSize = 10;
    Deque<Dummy> deque(newSize, dummy);

    for (size_t i = 0; i < deque.size(); ++i) {
        EXPECT_EQ(deque[i].data, dummy.data);
        EXPECT_EQ(deque.at(i).data, dummy.data);
    }

    EXPECT_EQ(deque.size(), newSize);

    EXPECT_EQ(11, TestHelper::existingCopies);
    EXPECT_EQ(1, TestHelper::constructorCnt);
    EXPECT_EQ(0, TestHelper::destructorCnt);
    EXPECT_EQ(10, TestHelper::copyConstructorCnt);
    EXPECT_EQ(0, TestHelper::copyAssignCnt);
    EXPECT_EQ(0, TestHelper::moveConstructorCnt);
    EXPECT_EQ(0, TestHelper::moveAssignCnt);
}

TEST_F(DequeTest, push_back_copy)
{
    Dummy dummy;
    Deque<Dummy> deque;
    deque.push_back(dummy);

    EXPECT_EQ(deque.size(), 1);

    EXPECT_EQ(2, TestHelper::existingCopies);
    EXPECT_EQ(1, TestHelper::constructorCnt);
    EXPECT_EQ(0, TestHelper::destructorCnt);
    EXPECT_EQ(1, TestHelper::copyConstructorCnt);
    EXPECT_EQ(0, TestHelper::copyAssignCnt);
    EXPECT_EQ(0, TestHelper::moveConstructorCnt);
    EXPECT_EQ(0, TestHelper::moveAssignCnt);
}

TEST_F(DequeTest, push_back_move)
{
    Dummy dummy;
    Deque<Dummy> deque;
    deque.push_back(std::move(dummy));

    EXPECT_EQ(deque.size(), 1);

    EXPECT_EQ(deque[0].data, Dummy::initialDataString);
    EXPECT_EQ(dummy.data, "");

    EXPECT_EQ(2, TestHelper::existingCopies);
    EXPECT_EQ(1, TestHelper::constructorCnt);
    EXPECT_EQ(0, TestHelper::destructorCnt);
    EXPECT_EQ(0, TestHelper::copyConstructorCnt);
    EXPECT_EQ(0, TestHelper::copyAssignCnt);
    EXPECT_EQ(1, TestHelper::moveConstructorCnt);
    EXPECT_EQ(0, TestHelper::moveAssignCnt);
}

TEST_F(DequeTest, emplace_back)
{
    Deque<Dummy> deque;

    const std::string myData = "MyData";

    deque.emplace_back(myData);
    EXPECT_EQ(deque.size(), 1);
    EXPECT_EQ(deque.back().data, myData);

    EXPECT_EQ(1, TestHelper::existingCopies);
    EXPECT_EQ(1, TestHelper::constructorCnt);
    EXPECT_EQ(0, TestHelper::destructorCnt);
    EXPECT_EQ(0, TestHelper::copyConstructorCnt);
    EXPECT_EQ(0, TestHelper::copyAssignCnt);
    EXPECT_EQ(0, TestHelper::moveConstructorCnt);
    EXPECT_EQ(0, TestHelper::moveAssignCnt);

    deque.emplace_back(myData);
    EXPECT_EQ(deque.size(), 2);
    EXPECT_EQ(deque.back().data, myData);

    EXPECT_EQ(2, TestHelper::existingCopies);
    EXPECT_EQ(2, TestHelper::constructorCnt);
    EXPECT_EQ(0, TestHelper::destructorCnt);
    EXPECT_EQ(0, TestHelper::copyConstructorCnt);
    EXPECT_EQ(0, TestHelper::copyAssignCnt);
    EXPECT_EQ(0, TestHelper::moveConstructorCnt);
    EXPECT_EQ(0, TestHelper::moveAssignCnt);
}

TEST_F(DequeTest, at_exception)
{
    Deque<Dummy> deque;

    EXPECT_ANY_THROW(deque.at(10););

    EXPECT_EQ(0, TestHelper::existingCopies);
    EXPECT_EQ(0, TestHelper::constructorCnt);
    EXPECT_EQ(0, TestHelper::destructorCnt);
    EXPECT_EQ(0, TestHelper::copyConstructorCnt);
    EXPECT_EQ(0, TestHelper::copyAssignCnt);
    EXPECT_EQ(0, TestHelper::moveConstructorCnt);
    EXPECT_EQ(0, TestHelper::moveAssignCnt);
}

TEST_F(DequeTest, pop_back)
{
    constexpr auto size = 1000;
    Deque<size_t> deque(size, 10);
    for (size_t i = 0; i < deque.size(); ++i) {
        deque[i] = i;
    }
    EXPECT_EQ(deque.size(), size);
    for (size_t i = 0; i < deque.size(); ++i) {
        EXPECT_EQ(deque[i], i);
    }
    constexpr auto newSize = size / 2;
    for (size_t i = 0; i < size - newSize; ++i) {
        deque.pop_back();
    }
    EXPECT_EQ(deque.size(), newSize);
    for (size_t i = 0; i < deque.size(); ++i) {
        EXPECT_EQ(deque[i], i);
    }
}

TEST_F(DequeTest, forCycle)
{
    constexpr auto size = 1000;
    Deque<size_t> deque(size, 0);
    {
        int i = 0;
        for (auto& element : deque) {
            element = i++;
        }
    }

    for (int i = 0; i < size - 1; ++i) {
        int j = i;
        for (auto element : deque) {
            EXPECT_EQ(element, j) << "Iteration " << i;
            ++j;
        }
        deque.pop_front();
    }
}