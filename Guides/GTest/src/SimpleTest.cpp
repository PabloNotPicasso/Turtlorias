#include "Dummy/DummyFunctions.hpp"

#include <gtest/gtest.h>

TEST(SimpleTestSuite, expectTrue)
{
    EXPECT_TRUE(Dummy::getTrue());
}

TEST(SimpleTestSuite, expectFalse)
{
    EXPECT_FALSE(Dummy::getFalse());
}

TEST(SimpleTestSuite, expectThrow)
{
    EXPECT_THROW(Dummy::throwInt(), int);
}

TEST(SimpleTestSuite, expectNoThrow)
{
    EXPECT_NO_THROW(Dummy::getTrue());
}

TEST(SimpleTestSuite, expectDeath)
{
    EXPECT_DEATH(Dummy::toAssert(), "Assertion `false' failed");
}

TEST(SimpleTestSuite, expectTrue_Fail)
{
    EXPECT_TRUE(Dummy::getFalse()) << "~~~~ We can add some description to the failure";

    // Some internal function of ::Test class
    EXPECT_FALSE(IsSkipped());
    EXPECT_TRUE(HasFailure());
    EXPECT_TRUE(HasNonfatalFailure());
    EXPECT_FALSE(HasFatalFailure());
}

TEST(SimpleTestSuite, assertTrue_Fail)
{
    // Test execution is stopped after assertion fail
    ASSERT_TRUE(Dummy::getFalse()) << "~~~~ Assertion test. It has to be failed)";

    // Will not be checked
    EXPECT_TRUE(false);
}

// Adding DISABLED_ prefix makes test 'skipped'
TEST(SimpleTestSuite, DISABLED_Test)
{
    // Will not be checked
    EXPECT_TRUE(false);
}

// Test can be skipped in run-time by calling GTEST_SKIP()
TEST(SimpleTestSuite, SkippedTest)
{
    GTEST_SKIP();

    // Will not be checked
    EXPECT_TRUE(false);
}