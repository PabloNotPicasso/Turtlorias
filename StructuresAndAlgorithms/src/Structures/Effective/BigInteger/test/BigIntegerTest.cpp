#include "Structures/Effective/BigInteger/BigInteger.h"
#include "Structures/Effective/BigInteger/Frame.h"

#include <gtest/gtest.h>

#include <sstream>

using namespace Structures;

TEST(Frame, init)
{
    Frame f;
    EXPECT_EQ(f, 0);
}

TEST(Frame, assign)
{
    auto assignCheck = [](Frame::value_t value) {
        Frame frame(value);
        EXPECT_EQ(frame, value);
    };

    assignCheck(0);
    assignCheck(12'345);
    assignCheck(-12'345);
    assignCheck(999'999);
    assignCheck(-999'999);
}

TEST(Frame, copy)
{
    auto copyCheck = [](Frame::value_t value) {
        Frame mainFrame;
        Frame toCopy(value);
        mainFrame = toCopy;
        EXPECT_EQ(mainFrame, value);
    };

    copyCheck(0);
    copyCheck(12'345);
    copyCheck(-12'345);
    copyCheck(999'999);
    copyCheck(-999'999);
}

TEST(BigInteger, toString)
{
    auto toStringCheck = [](int64_t value, std::string str) {
        BigInteger bi(value);
        EXPECT_EQ(bi.toString(), str);
    };

    toStringCheck(0, "0");
    toStringCheck(12345678, "12345678");
    toStringCheck(10000000000000, "10000000000000");
    toStringCheck(-561611981, "-561611981");
    toStringCheck(-10000000000000, "-10000000000000");
}

TEST(BigInteger, unaryMinus)
{
    auto unaryMinusCheck = [](int64_t value, std::string str) {
        BigInteger bi(value);
        EXPECT_EQ((-bi).toString(), str);
    };

    unaryMinusCheck(0, "0");
    unaryMinusCheck(12345678, "-12345678");
    unaryMinusCheck(10000000000000, "-10000000000000");
    unaryMinusCheck(-561611981, "561611981");
    unaryMinusCheck(-10000000000000, "10000000000000");
    {
        BigInteger bi(0);
        // Corner case
        EXPECT_EQ(bi, -bi);
        EXPECT_EQ((-bi).toString(), "0");
    }
}

TEST(BigInteger, isLess)
{
    auto isLessCheck = [](bool ans, int64_t lhs, int64_t rhs) {
        BigInteger biLhs(lhs);
        BigInteger biRhs(rhs);
        EXPECT_LT(biLhs, biRhs);
    };

    isLessCheck(true, 0, 10);
    isLessCheck(true, -10, 0);
    isLessCheck(true, -12412, 12412);
    isLessCheck(true, 12345678, 10000000000000);
    isLessCheck(true, 12345678, 561611981);
    isLessCheck(true, -10000000000000, -12412);
}

TEST(BigInteger, areEqual)
{
    auto areEqualCheck = [](int64_t value) {
        BigInteger biLhs(value);
        BigInteger biRhs(value);
        EXPECT_EQ(biLhs, biRhs);
    };

    areEqualCheck(0);
    areEqualCheck(10);
    areEqualCheck(12412);
    areEqualCheck(10000000000000);
    areEqualCheck(561611981);
    areEqualCheck(-12412);
    areEqualCheck(-10000000000000);
}

TEST(BigInteger, istream)
{
    auto istreamCheck = [](std::string expected) {
        BigInteger bi;
        std::stringstream ss;
        ss << expected;
        ss >> bi;
        EXPECT_EQ(bi.toString(), expected);
    };

    istreamCheck("120000000000000000000000000000000000000000");
    istreamCheck("1254618099800000000009784098798090987098018");
    istreamCheck("-1254618099800000000009784098798090987098018");
    istreamCheck("0");
    istreamCheck("-1");
    istreamCheck("-123456");
}

TEST(BigInteger, ostream)
{
    auto ostreamCheck = [](int64_t value) {
        BigInteger bi(value);
        std::stringstream biSS, intSS;
        biSS << bi;
        intSS << value;
        EXPECT_EQ(biSS.str(), intSS.str());
    };

    ostreamCheck(0);
    ostreamCheck(10);
    ostreamCheck(12412);
    ostreamCheck(10000000000000);
    ostreamCheck(561611981);
    ostreamCheck(-12412);
    ostreamCheck(-10000000000000);
}

TEST(BigInteger, sum)
{
    auto sumCheck = [](std::string lhs, std::string rhs, std::string sum) {
        BigInteger biLhs, biRhs, biSum;
        std::stringstream ss;
        ss << lhs << " " << rhs << " " << sum;
        ss >> biLhs >> biRhs >> biSum;
        EXPECT_EQ(biLhs + biRhs, biSum);
    };

    sumCheck("1", "999999", "1000000");

    sumCheck(
        "111111111111111111111111111111",
        "888888888888888888888888888888",
        "999999999999999999999999999999");

    sumCheck("1", "999999999999999999999999999999", "1000000000000000000000000000000");
}
