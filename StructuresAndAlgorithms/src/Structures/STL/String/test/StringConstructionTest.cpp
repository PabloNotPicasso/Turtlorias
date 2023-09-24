#include "StringTestFixture.h"

class StringConstruction : public StringTestFixture { };

TEST_F(StringConstruction, empty)
{
    String str;

    EXPECT_EQ(str.size(), 0);
}

TEST_F(StringConstruction, sizeConstruction)
{
    constexpr size_t size = 10;
    String str(size);

    EXPECT_EQ(str.size(), size);
    EXPECT_EQ(str.capacity(), size);

    for (size_t i = 0; i < str.size(); ++i) {
        EXPECT_EQ(str[i], String::nullTerminate);
    }
}

TEST_F(StringConstruction, NSymbolsConstruction)
{
    constexpr size_t size = 10;
    constexpr char symbol = 'o';
    String str(size, symbol);

    EXPECT_EQ(str.size(), size);
    EXPECT_EQ(str.capacity(), size);

    for (size_t i = 0; i < str.size(); ++i) {
        EXPECT_EQ(str[i], symbol);
    }
}

TEST_F(StringConstruction, initializerListConstruction)
{
    String str = {'a', 'b', 'c', 'd'};
    const auto initializerList = "abcd";
    for (size_t i = 0; i < str.size(); ++i) {
        EXPECT_EQ(str[i], initializerList[i]);
    }
}

TEST_F(StringConstruction, CStringConstruction)
{
    String str = "abcdefg";
    const auto initializerList = "abcdefg";
    for (size_t i = 0; i < str.size(); ++i) {
        EXPECT_EQ(str[i], initializerList[i]);
    }
}

TEST_F(StringConstruction, copyConstruction)
{
    String str(initializedString);

    EXPECT_EQ(str.size(), initializedString.size());
    for (size_t i = 0; i < str.size(); ++i) {
        EXPECT_EQ(str[i], initializedString[i]);
    }
}

TEST_F(StringConstruction, copyAssignConstruction)
{
    String str;
    str = initializedString;

    EXPECT_EQ(str.size(), initializedString.size());
    for (size_t i = 0; i < str.size(); ++i) {
        EXPECT_EQ(str[i], initializedString[i]);
    }
}

TEST_F(StringConstruction, moveConstruction)
{
    String copy = initializedString;
    String str(std::move(copy));

    EXPECT_EQ(copy.size(), 0);
    EXPECT_EQ(str.size(), initializedString.size());
    for (size_t i = 0; i < str.size(); ++i) {
        EXPECT_EQ(str[i], initializedString[i]);
    }
}

TEST_F(StringConstruction, moveAssignConstruction)
{
    String copy = initializedString;
    String str;
    str = std::move(copy);

    EXPECT_EQ(copy.size(), 0);
    EXPECT_EQ(str.size(), initializedString.size());
    for (size_t i = 0; i < str.size(); ++i) {
        EXPECT_EQ(str[i], initializedString[i]);
    }
}