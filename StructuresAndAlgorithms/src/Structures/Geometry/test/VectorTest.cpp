#include "Helpers/Helpers.h"
#include "Structures/Geometry/Vector.h"

#include <gtest/gtest.h>

using namespace Helpers;

TEST(Vector, construct)
{
    Vector::coordinate_t x = 10;
    Vector::coordinate_t y = -10;
    const Vector a(x, y);
    const Vector b(a);
    Vector c;
    c = b;
    const Vector d{x, y};

    EXPECT_EQ(a, b);
    EXPECT_EQ(a, c);
    EXPECT_EQ(a, d);

    EXPECT_NE(a, Vector());
}

TEST(Vector, compare_eq)
{
    Vector::coordinate_t x = 10;
    Vector::coordinate_t y = -10;
    const Vector a(x, y);
    const Vector b(x, y);

    EXPECT_TRUE(a == b);
    EXPECT_TRUE(a >= b);
    EXPECT_TRUE(a <= b);

    EXPECT_FALSE(a < b);
    EXPECT_FALSE(b > a);
    EXPECT_FALSE(a != b);
}

TEST(Vector, compare_less)
{
    const Vector a(0, 0);
    const Vector b(10, 0);

    EXPECT_TRUE(a != b);
    EXPECT_TRUE(a < b);
    EXPECT_TRUE(a <= b);
    EXPECT_TRUE(b > a);
    EXPECT_TRUE(b >= a);

    EXPECT_FALSE(a == b);
    EXPECT_FALSE(a > b);
    EXPECT_FALSE(b < a);
    EXPECT_FALSE(a >= b);
    EXPECT_FALSE(b <= a);
    EXPECT_FALSE(a == b);
}

TEST(Vector, compare_random)
{
    const Vector a = Helpers::getRandom<Vector>(-1e5, 1e5);
    const Vector b = Helpers::getRandom<Vector>(-1e5, 1e5);
    auto check = [](auto a, auto b) {
        EXPECT_EQ(a > b, !(a <= b));
        EXPECT_EQ(a < b, !(a >= b));
        EXPECT_EQ(a == b, !(a != b));
        EXPECT_EQ(a == b, (a >= b && a <= b));
        EXPECT_EQ(a != b, (a > b || a < b));

        EXPECT_NE(a != b, a == b);

        EXPECT_FALSE(a > b && a < b);
        EXPECT_FALSE(a == b && a < b);
        EXPECT_FALSE(a == b && a > b);
    };
    check(a, b);
    check(a, a);
    check(b, b);
}

TEST(Vector, operators_unary)
{
    const Vector v(1, -1);
    EXPECT_EQ(Vector(1, -1), v);
    EXPECT_EQ(Vector(1, -1), +v);
    EXPECT_EQ(Vector(-1, 1), -v);
}

TEST(Vector, operators_sum)
{
    const Vector a = Helpers::getRandom<Vector>(-1e5, 1e5);
    const Vector b = Helpers::getRandom<Vector>(-1e5, 1e5);
    Vector sum(0, 0);
    sum = a + b;

    EXPECT_EQ(b + a, a + b);
    EXPECT_EQ(a.x + b.x, Vector(a + b).x);
    EXPECT_EQ(a.x + b.x, Vector(a + b).x);
    EXPECT_EQ(Vector(a.x + b.x, a.y + b.y), a + b);
}

TEST(Vector, len)
{
    {
        const Vector v = Helpers::getRandom<Vector>(-1e5, 1e5);
        EXPECT_TRUE(areEqual(v.len(), sqrt(v.x * v.x + v.y * v.y)));
    }
    const Vector len10(0, 10);
    EXPECT_EQ(len10.len(), 10);
    {
        const Vector len5(3, 4);
        EXPECT_EQ(len5.len(), 5);
    }
    {
        const Vector len15(-15, 0);
        EXPECT_EQ(len15.len(), 15);
    }
}

TEST(Vector, norm)
{
    {
        Vector v = Helpers::getRandom<Vector>(-1e5, 1e5);
        v.norm();
        EXPECT_EQ(v.len(), 1);
    }

    {
        Vector len10(0, 10);
        len10.norm();
        EXPECT_EQ(len10.len(), 1);
        EXPECT_EQ(len10, Vector(0, 1));
    }
}

TEST(Vector, scalar)
{
    {
        const Vector a = Helpers::getRandom<Vector>(-1e5, 1e5);
        const Vector b = Helpers::getRandom<Vector>(-1e5, 1e5);
        EXPECT_TRUE(areEqual(Vector::scalar(a, b), (a.x * b.x + a.y * b.y)));
    }

    {
        const Vector a = Helpers::getRandom<Vector>(-1e5, 1e5);
        const Vector b(-a.y, a.x);
        EXPECT_TRUE(areEqual<double>(Vector::scalar(a, b), 0));
    }

    {
        const Vector a = Helpers::getRandom<Vector>(-1e5, 1e5);
        const Vector b(a);
        EXPECT_TRUE(areEqual(Vector::scalar(a, b), a.len() * b.len()));
    }
}

TEST(Vector, vectorProduct)
{
    {
        const Vector a = Helpers::getRandom<Vector>(-1e5, 1e5);
        const Vector b = Helpers::getRandom<Vector>(-1e5, 1e5);
        EXPECT_TRUE(areEqual(Vector::vectorProduct(a, b), (a.x * b.y - a.y * b.x)));
    }

    {
        const Vector a = Helpers::getRandom<Vector>(-1e5, 1e5);
        const Vector b(-a.y, a.x);
        EXPECT_TRUE(areEqual(Vector::vectorProduct(a, b), a.len() * b.len()));
    }

    {
        const Vector a = Helpers::getRandom<Vector>(-1e5, 1e5);
        const Vector b(a);
        EXPECT_TRUE(areEqual<double>(Vector::vectorProduct(a, b), 0));
    }
}