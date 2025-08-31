#include "VectorIteratorFixture.h"

class VectorRandomAccessIteratorTest : public BaseVectorIteratorTest { };

using namespace Structures::STL;

TEST_F(VectorRandomAccessIteratorTest, integer_sum)
{
    const VectorIterator begin(vector.begin());
    const VectorIterator mid(vector.begin() + vector.size() / 2);
    const VectorIterator end(vector.begin() + vector.size());

    auto size = vector.size();
    EXPECT_EQ(begin + size / 2, end - size / 2);
    EXPECT_EQ(begin + size / 2, mid);
    EXPECT_EQ(mid, end - size / 2);

    EXPECT_EQ(begin + size, end);
    EXPECT_EQ(end - size, begin);
    EXPECT_EQ(end - begin, size);
}

TEST_F(VectorRandomAccessIteratorTest, greater_less)
{
    const VectorIterator begin(vector.begin());
    const VectorIterator mid(vector.begin() + vector.size() / 2);
    const VectorIterator end(vector.begin() + vector.size());

    EXPECT_TRUE(begin < mid);
    EXPECT_TRUE(begin < end);
    EXPECT_TRUE(begin <= begin);
    EXPECT_TRUE(begin >= begin);

    EXPECT_TRUE(begin + vector.size() > mid);
}
