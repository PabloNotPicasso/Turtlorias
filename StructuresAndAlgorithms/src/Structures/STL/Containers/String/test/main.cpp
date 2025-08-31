#include <gtest/gtest.h>

#include "StringConstructionTest.cpp"
#include "StringOperatorTest.cpp"
#include "StringTest.cpp"

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
