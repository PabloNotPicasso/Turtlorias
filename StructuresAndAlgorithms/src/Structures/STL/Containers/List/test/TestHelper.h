#pragma once

#include <gtest/gtest.h>

class TestHelper {
public:
    static int existingCopies;
    static int constructorCnt;
    static int destructorCnt;
    static int copyConstructorCnt;
    static int copyAssignCnt;
    static int moveConstructorCnt;
    static int moveAssignCnt;

    static void reset()
    {
        TestHelper::existingCopies = 0;
        TestHelper::constructorCnt = 0;
        TestHelper::destructorCnt = 0;
        TestHelper::copyConstructorCnt = 0;
        TestHelper::copyAssignCnt = 0;
        TestHelper::moveConstructorCnt = 0;
        TestHelper::moveAssignCnt = 0;
    }
};
int TestHelper::existingCopies = 0;
int TestHelper::constructorCnt = 0;
int TestHelper::destructorCnt = 0;
int TestHelper::copyConstructorCnt = 0;
int TestHelper::copyAssignCnt = 0;
int TestHelper::moveConstructorCnt = 0;
int TestHelper::moveAssignCnt = 0;

class Dummy {
public:
    static constexpr std::string_view initialDataString = "InitialDataString";
    std::string data;

    Dummy()
        : Dummy(initialDataString)
    {
    }

    Dummy(const std::string_view& dataToInitialize)
        : data(dataToInitialize)
    {
        ++TestHelper::constructorCnt;
        ++TestHelper::existingCopies;
    }

    ~Dummy()
    {
        ++TestHelper::destructorCnt;
        --TestHelper::existingCopies;
    }
    Dummy(const Dummy& toCopy)
        : data(toCopy.data)
    {
        ++TestHelper::copyConstructorCnt;
        ++TestHelper::existingCopies;
    }
    Dummy& operator=(const Dummy& toCopy)
    {
        data = toCopy.data;
        ++TestHelper::copyAssignCnt;
        return *this;
    }
    Dummy(Dummy&& toCopy)
        : data(std::move(toCopy.data))
    {
        ++TestHelper::moveConstructorCnt;
        ++TestHelper::existingCopies;
    }
    Dummy& operator=(Dummy&& toCopy)
    {
        data = std::move(toCopy.data);
        ++TestHelper::moveAssignCnt;
        return *this;
    }
};

class ListTestBase : public testing::Test {
protected:
    void SetUp() override
    {
        withDataDummy = Dummy("SomeOtherData");
        TestHelper::reset();
    }

    Dummy uninitializedDummy;
    Dummy withDataDummy;
};