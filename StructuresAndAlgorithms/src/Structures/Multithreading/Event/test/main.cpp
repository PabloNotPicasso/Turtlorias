#include <gtest/gtest.h>

// clang-format off
#include "EventTest.cpp"
// clang-format on

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}