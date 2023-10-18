#include "Structures/STL/Deque/Deque.h"
#include "TestHelper.h"

using namespace Structures::STL;

class DequeTest : public testing::Test {
protected:
    void SetUp() override
    {
        withDataDummy = Dummy("SomeOtherData");
        TestHelper::reset();
    }

    Dummy uninitializedDummy;
    Dummy withDataDummy;
};

TEST_F(DequeTest, creation_empty)
{
    Deque<Dummy> deque;

    EXPECT_EQ(deque.size(), 0);
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
}

TEST_F(DequeTest, push_back_copy)
{
    Dummy dummy;
    Deque<Dummy> deque;
    deque.push_back(dummy);

    EXPECT_EQ(deque.size(), 1);
}

TEST_F(DequeTest, at_exception)
{
    Deque<Dummy> deque;

    EXPECT_ANY_THROW(deque.at(10););
}
