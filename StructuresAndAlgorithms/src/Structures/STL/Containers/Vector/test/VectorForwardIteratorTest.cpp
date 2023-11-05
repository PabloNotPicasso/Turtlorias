#include "VectorIteratorFixture.h"

class VectorForwardIteratorTest : public BaseVectorIteratorTest { };

using namespace Structures::STL;

TEST_F(VectorForwardIteratorTest, increment)
{
    VectorIterator it1(vector.begin());
    VectorIterator expected(vector.begin());

    EXPECT_EQ(it1++, expected);
    EXPECT_EQ(it1, ++expected);

    auto it2 = it1;
    EXPECT_EQ(it1++, it2);
    EXPECT_EQ(it1, ++it2);

    EXPECT_NE(it1, expected);
    EXPECT_NE(it2, expected);
}

TEST_F(VectorForwardIteratorTest, advance_incremental)
{
    VectorIterator it(vector.begin());
    const VectorIterator mid(vector.begin() + vector.size() / 2);
    const VectorIterator end(vector.end());

    std::advance(it, vector.size() / 2);
    EXPECT_EQ(it, mid);

    std::advance(it, vector.size() / 2);
    EXPECT_EQ(it, end);
}