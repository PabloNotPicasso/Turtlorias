#pragma once
#include "Dummy/DummyClass.hpp"

#include <gtest/gtest.h>
#include <iostream>

class DummyFixture : public ::testing::Test {
protected:
    // SetUp is calling at the begining of the each test case (set of tests)
    // Same as SetUpTestCase
    static void SetUpTestSuite()
    {
        ++DummyFixture::testSuiteCounter;
        DummyFixture::testCounter = 0;
        std::cout << std::string(80, '_') << '\n';
        std::cout << "Test Suite #" << DummyFixture::testSuiteCounter << " SetUp \n";

        DummyFixture::pDummyStatic = new DummyClass();
    }

    // TearDown is calling at the end of the each test case (set of tests)
    // Same as TearDownTestCase
    static void TearDownTestSuite()
    {
        std::cout << "Test Suite #" << DummyFixture::testSuiteCounter << " TearDown \n";
        std::cout << std::string(80, '_') << '\n';

        delete DummyFixture::pDummyStatic;
    }

private:
    // SetUp is calling at the begining of the each test
    void SetUp() override
    {
        ++DummyFixture::testCounter;
        std::cout << "#" << DummyFixture::testCounter << " Test SetUp \n";
    }
    // TearDown is calling at the end of the each test
    void TearDown() override
    {
        std::cout << "#" << DummyFixture::testCounter << " Test TearDown \n";
    }

protected:
    DummyClass dummy;
    static DummyClass* pDummyStatic;
    static int testCounter;
    static int testSuiteCounter;
};

DummyClass* DummyFixture::pDummyStatic;
int DummyFixture::testCounter = 0;
int DummyFixture::testSuiteCounter = 0;
