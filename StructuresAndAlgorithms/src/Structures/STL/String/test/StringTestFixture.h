#pragma once

#include "Structures/STL/String/String.h"

#include <gtest/gtest.h>

using namespace Structures;

class StringTestFixture : public testing::Test {
public:
    void SetUp() override
    {
        initializedString = cStringData;
    }

    String initializedString;
    constexpr static auto cStringData = "SomeDataToInitialize";
};