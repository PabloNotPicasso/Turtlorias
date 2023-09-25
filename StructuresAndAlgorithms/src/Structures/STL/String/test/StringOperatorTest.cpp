#include "StringTestFixture.h"

class StringOperator : public StringTestFixture { };

TEST_F(StringOperator, sameString)
{
    const String str = cStringData;
    EXPECT_EQ(str, str);
    EXPECT_TRUE(str == str);
    EXPECT_TRUE(str >= str);
    EXPECT_TRUE(str <= str);

    EXPECT_FALSE(str != str);
    EXPECT_FALSE(str > str);
    EXPECT_FALSE(str < str);

    String sameStringExtended = str;
    sameStringExtended.reserve(str.capacity() * 2);
    EXPECT_TRUE(str == sameStringExtended);
    EXPECT_EQ(str, sameStringExtended);
}

TEST_F(StringOperator, initializedString)
{
    const String str = initializedString;
    EXPECT_TRUE(str == initializedString);
    EXPECT_TRUE(str >= initializedString);
    EXPECT_TRUE(str <= initializedString);

    EXPECT_FALSE(str != initializedString);
    EXPECT_FALSE(str > initializedString);
    EXPECT_FALSE(str < initializedString);
}

TEST_F(StringOperator, cString)
{
    const String str = cStringData;
    EXPECT_TRUE(str == cStringData);
    EXPECT_TRUE(str >= cStringData);
    EXPECT_TRUE(str <= cStringData);

    EXPECT_FALSE(str != cStringData);
    EXPECT_FALSE(str > cStringData);
    EXPECT_FALSE(str < cStringData);
}

TEST_F(StringOperator, areEqual)
{
    const String str = initializedString;
    EXPECT_TRUE(str == initializedString);
}

TEST_F(StringOperator, sumAssign)
{
    String str = "abc";

    const String expectedSumString = "abcdef";
    const String toAdd("def");
    str += toAdd;
    EXPECT_EQ(str, expectedSumString);

    const String expectedSumChar = "abcdef0";
    str += '0';
    EXPECT_EQ(str, expectedSumChar);

    const String expectedSumCharArray = "abcdef01234";
    str += "1234";
    EXPECT_EQ(str, expectedSumCharArray);
    EXPECT_EQ(str.size(), expectedSumCharArray.size());
}

TEST_F(StringOperator, sum)
{
    const String lhs = "abc";
    const String rhs = "def";
    const String expected = "abcdef01234";

    String sum = lhs + rhs + '0' + "1234";
    EXPECT_EQ(sum, expected);
}
