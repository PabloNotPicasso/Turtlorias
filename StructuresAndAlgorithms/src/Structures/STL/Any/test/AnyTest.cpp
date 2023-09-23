#include "Structures/STL/Any/Any.h"

#include <gtest/gtest.h>

using namespace Structures;

TEST(Any, empty_constructor)
{
    Any any_obj;
    EXPECT_FALSE(any_obj.is<int>());
}

TEST(Any, constructor)
{
    int iNum = 123;
    Any any_obj(iNum);
    EXPECT_TRUE(any_obj.is<int>());
    EXPECT_EQ(any_obj.as<int>(), iNum);

    EXPECT_FALSE(any_obj.is<bool>());
}

TEST(Any, reset)
{
    int iNum = 123;
    Any any_obj(iNum);
    any_obj.reset();
    EXPECT_FALSE(any_obj.is<int>());
}

TEST(Any, assignOperator)
{
    int iNum = 123;
    Any any_obj = iNum;
    EXPECT_TRUE(any_obj.is<int>());
    EXPECT_EQ(any_obj.as<int>(), iNum);

    std::string str = "123";
    any_obj = str;
    EXPECT_TRUE(any_obj.is<std::string>());
    EXPECT_EQ(any_obj.as<std::string>(), str);
}