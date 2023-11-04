#include <gtest/gtest.h>

// clang-format off
#include "BaseInputIteratorTest.cpp"
#include "BaseForwardIteratorTest.cpp"
#include "BaseBidirectionalIteratorTest.cpp"
#include "BaseRandomAccessIteratorTest.cpp"
#include "ArrayCreationTest.cpp"
// clang-format on

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}