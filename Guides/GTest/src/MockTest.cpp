#include "DummyMock.hpp"

#include <memory>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace ::testing;

class DummyFixture : public ::Test {
protected:
    void clear(){
        /*
            Expect's lifetime depends on object's lifetime!
            It doesn't depends on Test lifetime
            So its better to clear Expectations after every test
              calling Mock::VerifyAndClearExpectations    
        */
        Mock::VerifyAndClearExpectations(dummyMock);
    }

private:
    void SetUp() override
    {
        /*
            Gtest is trying to detect leaks so it creates warnings
              in case object still exist after Test ending
            To suppress warning use AllowLeak
        */
        Mock::AllowLeak(dummyMock);
    
        // NiceMock allows uninterested mocks
        dummyMock = new NiceMock<DummyMock>();
        dummyWrapper = new DummyWrapper(dummyMock);
    }
    void TearDown() override
    {
        clear();
        delete dummyMock;
        delete dummyWrapper;
    }

protected:
    DummyMock* dummyMock;
    DummyWrapper* dummyWrapper;
};

// @Times
TEST_F(DummyFixture, Times)
{
    int n = 10;
    // Expects exactly n times to be called
    EXPECT_CALL(*dummyMock, getTrue()).Times(n);
    dummyWrapper->callGetTrueNTimes(n);
}

TEST_F(DummyFixture, Times_Cardinality)
{
    int n = 10;

    EXPECT_CALL(*dummyMock, getTrue()).Times( AtLeast(n) );
    dummyWrapper->callGetTrueNTimes(n+n);
    clear();

    EXPECT_CALL(*dummyMock, getTrue()).Times( AtMost(n) );
    dummyWrapper->callGetTrueNTimes(n/2);
    clear();

    EXPECT_CALL(*dummyMock, getTrue()).Times( Between(n, n+10) );
    dummyWrapper->callGetTrueNTimes(n+1);
}

TEST_F(DummyFixture, expectCall_WillOnce)
{
    EXPECT_CALL(*dummyMock, getInt(_)).WillOnce( Return(1));
    dummyWrapper->callGetInt(1);
    // Cannot be called
    // dummyWrapper->callGetInt(2);
}

TEST_F(DummyFixture, expectCall_WithExpectedValue)
{
    int expectedInt = 12;
    EXPECT_CALL(*dummyMock, getInt(expectedInt));

    dummyWrapper->callGetInt(expectedInt);
}

TEST_F(DummyFixture, expectCall_AfterExpectationSet)
{
    ExpectationSet precondition;
    precondition += EXPECT_CALL(*dummyMock, getInt(1)); 
    precondition += EXPECT_CALL(*dummyMock, getInt(2));
    precondition += EXPECT_CALL(*dummyMock, getInt(3));

    EXPECT_CALL(*dummyMock, getTrue()).Times(1).After( precondition );

    dummyWrapper->callGetInt(1);
    dummyWrapper->callGetInt(2);
    dummyWrapper->callGetInt(3);

    // Can be called even if it's not in sequence
    dummyWrapper->callGetFalse();

    dummyWrapper->callGetTrue();
}

TEST_F(DummyFixture, expectCall_InSequence)
{
    // Just create it on stack to put every Expectation in sequence
    InSequence dummy;

    EXPECT_CALL(*dummyMock, getInt(1)); 
    EXPECT_CALL(*dummyMock, getInt(2));
    EXPECT_CALL(*dummyMock, getInt(3));

    EXPECT_CALL(*dummyMock, getTrue()).Times(1);

    dummyWrapper->callGetInt(1);
    dummyWrapper->callGetInt(2);
    dummyWrapper->callGetInt(3);

    // Can be called even if it's not in sequence
    dummyWrapper->callGetFalse();

    dummyWrapper->callGetTrue();
}

TEST_F(DummyFixture, expectCall_Sequence)
{
    Sequence precondition;
    precondition.AddExpectation( EXPECT_CALL(*dummyMock, getInt(1)) ); 
    precondition.AddExpectation( EXPECT_CALL(*dummyMock, getInt(2)) );
    precondition.AddExpectation( EXPECT_CALL(*dummyMock, getInt(3)) );

    EXPECT_CALL(*dummyMock, getTrue()).Times(1).InSequence( precondition );

    dummyWrapper->callGetInt(1);
    dummyWrapper->callGetInt(2);
    dummyWrapper->callGetInt(3);

    // Can be called even if it's not in sequence
    dummyWrapper->callGetFalse();

    dummyWrapper->callGetTrue();
}