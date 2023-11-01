#pragma once

#include "Structures/STL/Containers/String/String.h"

#include <gtest/gtest.h>

using namespace Structures::STL;

class StringTestFixture : public testing::Test {
public:
    void SetUp() override
    {
        initializedString = cStringData;
    }

    String initializedString;
    constexpr static auto cStringData = "SomeDataToInitialize";
};
