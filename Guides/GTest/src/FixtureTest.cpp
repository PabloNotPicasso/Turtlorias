#include "DummyFixture.hpp"

// To set fixture use TEST_F() 

TEST_F(DummyFixture, expectTrue)
{
    EXPECT_TRUE(dummy.getTrue());
}

TEST_F(DummyFixture, expectFalse)
{
    EXPECT_FALSE(dummy.getFalse());
}

// TODO: Should fail in case of --gtest_shuffle
TEST_F(DummyFixture, increasingCounter_0)
{
    EXPECT_EQ(pDummyStatic->getIncreasingCounter(), 0);
}

TEST_F(DummyFixture, increasingCounter_1)
{
    EXPECT_EQ(pDummyStatic->getIncreasingCounter(), 1);
}

/*
There is a little trick
We can use it to create new test case
*/
class AnotherTestCase : public DummyFixture {
};

/*
So these tests will be executed separatly
Can be used in case of order-dependent tests
*/
TEST_F(AnotherTestCase, expectTrue)
{
    EXPECT_TRUE(dummy.getTrue());
}

TEST_F(AnotherTestCase, expectFalse)
{
    EXPECT_FALSE(dummy.getFalse());
}

TEST_F(AnotherTestCase, increasingCounter_0)
{
    EXPECT_EQ(pDummyStatic->getIncreasingCounter(), 0);
}

TEST_F(AnotherTestCase, increasingCounter_1)
{
    EXPECT_EQ(pDummyStatic->getIncreasingCounter(), 1);
}