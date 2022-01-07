#pragma once
#include "Dummy/DummyClass.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

class DummyMock : public DummyClass
{
public:

    MOCK_METHOD0(getTrue, bool(void));

    MOCK_METHOD0(getFalse, bool(void));

    MOCK_METHOD1(getInt, int(int numberToReturn) );
};