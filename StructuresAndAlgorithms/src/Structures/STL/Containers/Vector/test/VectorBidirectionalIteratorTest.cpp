#include "VectorIteratorFixture.h"

class VectorBidirectionalIteratorTest : public BaseVectorIteratorTest { };

using namespace Structures::STL;

TEST_F(VectorBidirectionalIteratorTest, decrement)
{
    VectorIterator it(vector.begin());
    const VectorIterator begin(vector.begin());

    ++it;
    EXPECT_NE(begin, it--);
    EXPECT_EQ(begin, it);

    ++it;
    EXPECT_EQ(begin, --it);
    EXPECT_EQ(begin, it);
}

TEST_F(VectorBidirectionalIteratorTest, advance_decremental)
{
    VectorIterator lIt(vector.begin());
    VectorIterator rIt(vector.end());

    std::advance(lIt, vector.size() / 2);
    std::advance(rIt, -vector.size() / 2);
    EXPECT_EQ(lIt, rIt);
}
