#include <gtest/gtest.h>

// clang-format off
#include "VectorInputIteratorTest.cpp"
#include "VectorForwardIteratorTest.cpp"
#include "VectorBidirectionalIteratorTest.cpp"
#include "VectorRandomAccessIteratorTest.cpp"
#include "VectorTest.cpp"
// clang-format on

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}