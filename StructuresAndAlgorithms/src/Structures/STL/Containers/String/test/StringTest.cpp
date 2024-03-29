#include "StringTestFixture.h"

class StringTest : public StringTestFixture { };

TEST_F(StringTest, reserve)
{
    size_t newSize = 10;
    String str;

    str.reserve(newSize);

    EXPECT_EQ(str.size(), 0);
    EXPECT_EQ(str.capacity(), newSize);
}

TEST_F(StringTest, resize_empty)
{
    size_t newSize = 10;
    String str;

    str.resize(newSize);

    EXPECT_EQ(str.size(), newSize);
    EXPECT_EQ(str.capacity(), newSize);

    for (size_t i = 0; i < str.size(); ++i) {
        EXPECT_EQ(str[i], String::nullTerminate);
    }
}

TEST_F(StringTest, resize_with_value)
{
    char toFill = 'a';
    size_t newSize = 10;
    String str;

    str.resize(newSize, toFill);

    EXPECT_EQ(str.size(), newSize);
    EXPECT_EQ(str.capacity(), newSize);

    for (size_t i = 0; i < str.size(); ++i) {
        EXPECT_EQ(str[i], toFill);
    }
}

TEST_F(StringTest, push_back_copy)
{
    char toFill = 'a';
    String str;
    str.push_back(toFill);

    EXPECT_EQ(str.size(), 1);
    EXPECT_EQ(str.capacity(), 1);
}

TEST_F(StringTest, at_exception)
{
    String str;

    EXPECT_ANY_THROW(str.at(10););
}

TEST_F(StringTest, insert)
{
    char toFill = 'a';
    char toInsert = 'b';
    const size_t size = 10;
    const size_t newSize = size + 1;
    const size_t insertPosition = 5;
    String str(size, toFill);

    str.insert(insertPosition, toInsert);

    EXPECT_EQ(str.size(), newSize);
    EXPECT_EQ(str.capacity(), size * 2);

    EXPECT_EQ(str[insertPosition], toInsert);
    for (size_t i = 0; i < insertPosition; ++i) {
        EXPECT_EQ(str[i], toFill);
    }
    for (size_t i = insertPosition + 1; i < newSize; ++i) {
        EXPECT_EQ(str[i], toFill);
    }
}

TEST_F(StringTest, rangeBasedFor)
{
    const String str = "0123456789";

    String accumulator;

    for (auto c : str) {
        accumulator.push_back(c);
    }

    EXPECT_EQ(accumulator, str);
}