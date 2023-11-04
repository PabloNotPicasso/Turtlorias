#include "Helpers/TestHelper.h"
#include "Structures/STL/Containers/Vector/Vector.h"

using namespace Structures::STL;

class VectorIteratorTest : public BaseTest { };

TEST_F(VectorIteratorTest, emptyVector)
{
    Vector<Dummy> emptyVector;

    EXPECT_EQ(emptyVector.size(), 0);
    EXPECT_EQ(emptyVector.begin(), emptyVector.end());
    EXPECT_EQ(emptyVector.cbegin(), emptyVector.cend());
}

TEST_F(VectorIteratorTest, increment)
{
    constexpr auto size = 5;
    Vector<int> Vector(size, 0);

    auto it = Vector.begin();

    EXPECT_EQ(it++, Vector.begin());
    EXPECT_EQ(it, ++Vector.begin());

    auto secondElementIt = it;
    EXPECT_EQ(it++, secondElementIt);
    EXPECT_EQ(it, ++secondElementIt);

    EXPECT_NE(it, Vector.begin());
    EXPECT_NE(secondElementIt, Vector.begin());
}

TEST_F(VectorIteratorTest, decrement)
{
    constexpr auto size = 5;
    Vector<int> Vector(size, 0);

    auto firstElementIt = Vector.begin();
    auto secondElementIt = std::next(firstElementIt);

    EXPECT_NE(firstElementIt, secondElementIt--);
    EXPECT_EQ(firstElementIt, secondElementIt);
    ++secondElementIt;

    EXPECT_EQ(firstElementIt, --secondElementIt);
    EXPECT_EQ(firstElementIt, secondElementIt);
}

TEST_F(VectorIteratorTest, advance)
{
    constexpr auto size = 5;
    Vector<int> Vector(size, 0);
    auto lIt = Vector.begin();
    auto rIt = Vector.end();
    std::advance(lIt, 2);
    std::advance(rIt, -3);

    EXPECT_EQ(lIt, rIt);
}