#include "VectorIteratorFixture.h"

class VectorInputIteratorTest : public BaseVectorIteratorTest { };

using namespace Structures::STL;

TEST_F(VectorInputIteratorTest, creation)
{
    VectorIterator it1(vector.begin());
    VectorIterator copy(it1);
    VectorIterator copyAssign;
    copyAssign = it1;

    EXPECT_EQ(it1, copy);
    EXPECT_EQ(it1, copyAssign);
    EXPECT_EQ(copy, copyAssign);
}

TEST_F(VectorInputIteratorTest, equality_Check)
{
    VectorIterator it1(vector.begin());
    VectorIterator it1_same(vector.begin());
    VectorIterator it2(vector.begin() + 5);

    EXPECT_EQ(it1, it1_same);
    EXPECT_NE(it1, it2);

    EXPECT_EQ(it1, it1);
    EXPECT_EQ(it2, it2);
}