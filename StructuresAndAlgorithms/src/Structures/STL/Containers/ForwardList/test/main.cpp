#include <gtest/gtest.h>

#include "ForwardListAddValueTest.cpp"
#include "ForwardListCreationTest.cpp"
#include "ForwardListIteratorTest.cpp"

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}