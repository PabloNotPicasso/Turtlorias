#include <gtest/gtest.h>

#include "ListAddValueTest.cpp"
#include "ListCreationTest.cpp"
#include "ListIteratorTest.cpp"

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
