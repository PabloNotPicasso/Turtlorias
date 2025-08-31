#include "Structures/STL/Containers/Tuple/Tuple.h"

#include <gtest/gtest.h>

#include <algorithm>
#include <string>
#include <vector>

using namespace Structures::STL;

TEST(TupleTest, assign)
{
    Tuple<int, double, std::string> t;

    int val0 = 10;
    double val1 = 0.5;
    std::string val2 = "test";

    EXPECT_NE(get<0>(t), val0);
    EXPECT_NE(get<1>(t), val1);
    EXPECT_NE(get<2>(t), val2);

    get<0>(t) = val0;
    get<1>(t) = val1;
    get<2>(t) = val2;

    EXPECT_EQ(get<0>(t), val0);
    EXPECT_EQ(get<1>(t), val1);
    EXPECT_EQ(get<2>(t), val2);
}

TEST(TupleTest, compare)
{
    Tuple<int, double, std::string> t1;
    Tuple<int, double, std::string> t2;

    int val0 = 10;
    double val1 = 0.5;
    std::string val2 = "asdsg";

    get<0>(t1) = val0;
    get<1>(t1) = val1;
    get<2>(t1) = val2;

    EXPECT_TRUE(t1 != t2);
    EXPECT_NE(t1, t2);

    get<0>(t2) = val0;
    get<1>(t2) = val1;
    get<2>(t2) = val2;

    EXPECT_TRUE(t1 == t2);
    EXPECT_EQ(t1, t2);

    get<0>(t2) = get<0>(t1) + 10;

    EXPECT_TRUE(t1 < t2);
}

TEST(TupleTest, sort)
{
    int N = 10;
    std::vector<Tuple<int, int>> v(N);

    for (int i = 0; i < N; ++i) {
        get<0>(v[i]) = N - i - 1;
        get<1>(v[i]) = i;
    }
    sort(v.begin(), v.end());

    for (int i = 0; i < N; ++i) {
        EXPECT_EQ(get<0>(v[i]), i);
        EXPECT_EQ(get<1>(v[i]), N - i - 1);
    }
}
