#pragma once

#include "Helpers/Helpers.h"
#include "Point.h"

#include <cmath>

template<typename Coordinate>
class BaseVector {
public:
    using coordinate_t = Coordinate;
    using distance_t = double;
    coordinate_t x;
    coordinate_t y;

public:
    BaseVector()
        : x(0)
        , y(0)
    {
    }

    BaseVector(const coordinate_t c)
        : x(c)
        , y(c)
    {
    }

    BaseVector(const coordinate_t _x, const coordinate_t _y)
        : x(_x)
        , y(_y)
    {
    }

    BaseVector operator+() const
    {
        return *this;
    }
    BaseVector operator-() const
    {
        return BaseVector(-x, -y);
    }

    BaseVector& operator++()
    {
        ++(this->x);
        ++(this->y);
        return *this;
    }
    BaseVector& operator--()
    {
        --(this->x);
        --(this->y);
        return *this;
    }

    BaseVector& operator+=(const BaseVector toAdd)
    {
        this->x += toAdd.x;
        this->y += toAdd.y;
        return *this;
    }
    BaseVector& operator-=(const BaseVector toMinus)
    {
        this->x -= toMinus.x;
        this->y -= toMinus.y;
        return *this;
    }

    BaseVector& operator*=(const BaseVector toMultiply)
    {
        this->x *= toMultiply.x;
        this->y *= toMultiply.y;
        return *this;
    }
};

template<typename Coordinate>
BaseVector<Coordinate> operator+(const BaseVector<Coordinate> lhs, const BaseVector<Coordinate> rhs)
{
    BaseVector<Coordinate> sum = lhs;
    sum += rhs;
    return sum;
}

template<typename Coordinate>
BaseVector<Coordinate> operator-(const BaseVector<Coordinate> lhs, const BaseVector<Coordinate> rhs)
{
    BaseVector<Coordinate> difference = lhs;
    difference -= rhs;
    return difference;
}

template<typename Coordinate>
BaseVector<Coordinate> operator*(const BaseVector<Coordinate> lhs, const BaseVector<Coordinate> rhs)
{
    BaseVector<Coordinate> product = lhs;
    product *= rhs;
    return product;
}

/**
 * @brief This operator could be used in std::map
 */
template<typename Coordinate>
bool operator<(const BaseVector<Coordinate> lhs, const BaseVector<Coordinate> rhs)
{
    return lhs.x < rhs.x || (lhs.x == rhs.x && lhs.y < rhs.y);
}
template<typename Coordinate>
bool operator>(const BaseVector<Coordinate> lhs, const BaseVector<Coordinate> rhs)
{
    return rhs < lhs;
}
template<typename Coordinate>
bool operator<=(const BaseVector<Coordinate> lhs, const BaseVector<Coordinate> rhs)
{
    return !(lhs > rhs);
}
template<typename Coordinate>
bool operator>=(const BaseVector<Coordinate> lhs, const BaseVector<Coordinate> rhs)
{
    return !(lhs < rhs);
}

template<typename Coordinate>
bool operator==(const BaseVector<Coordinate> lhs, const BaseVector<Coordinate> rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}
template<typename Coordinate>
bool operator!=(const BaseVector<Coordinate> lhs, const BaseVector<Coordinate> rhs)
{
    return !(lhs == rhs);
}

template<typename Coordinate>
std::ostream& operator<<(std::ostream& os, const BaseVector<Coordinate> v)
{
    os << "BaseVector<Coordinate>(" << v.x << ", " << v.y << ")";
    return os;
}

template<typename Coordinate>
std::istream& operator>>(std::istream& is, BaseVector<Coordinate>& v)
{
    is >> v.x >> v.y;
    return is;
}

class Vector : public BaseVector<double> {
public:
    Vector()
        : BaseVector(0, 0)
    {
    }
    Vector(const coordinate_t c)
        : BaseVector(c, c)
    {
    }
    Vector(const coordinate_t _x, const coordinate_t _y)
        : BaseVector(_x, _y)
    {
    }
    Vector(const Point start, const Point end)
        : BaseVector((end.x - start.x), (end.y - start.y))
    {
    }
    Vector(const BaseVector& toCopy)
        : Vector(toCopy.x, toCopy.y)
    {
    }
    Vector& operator=(const BaseVector& toCopy)
    {
        x = toCopy.x;
        y = toCopy.y;
        return *this;
    }

    void norm()
    {
        auto lenght = len();
        x /= lenght;
        y /= lenght;
    }

    double len() const
    {
        return sqrt(x * x + y * y);
    }

    /**
     * @brief Scalar product
     * Scalar product of vectors A and B
     *
     * scalar = ax * bx + ay * by
     *
     * scalar = |a| * |b| * cos(a,b)
     *
     * so, if scalar >  0 angle (a,b) < 90*
     *     if scalar <  0 angle (a,b) > 90*
     *     if scalar =  0 angle (a,b) = 90*  - vectors are perpendicular
     *     if scalar =  1 angle (a,b) = 0*   - vectors are coliniar
     *     if scalar = -1 angle (a,b) = 180* - vectors are coliniar, but have different directions
     */
    static double scalar(const Vector lhs, const Vector rhs)
    {
        return lhs.x * rhs.x + lhs.y * rhs.y;
    }

    /**
     * @brief Vector product
     * Vector product of vectors A and B
     *
     * vecProd = ax * by - ay * bx
     *
     * vecProd = |a| * |b| * sin(a,b)
     *
     * vecProd = S(ab) - parallelogram area
     *
     * so, if vecProd >  0 angle (a,b) > 0*
     *     if vecProd <  0 angle (a,b) < 0*
     *     if vecProd =  0 angle (a,b) = 0*   - vectors are coliniar
     *     if vecProd =  1 angle (a,b) = 90*  - vectors are perpendicular
     *     if vecProd = -1 angle (a,b) = -90* - vectors are perpendicular
     */
    static double vectorProduct(const Vector lhs, const Vector rhs)
    {
        return lhs.x * rhs.y - lhs.y * rhs.x;
    }

    static double sinBetween(const Vector lhs, const Vector rhs)
    {
        return Vector::vectorProduct(lhs, rhs) / lhs.len() / rhs.len();
    }

    static double cosBetween(const Vector lhs, const Vector rhs)
    {
        return Vector::scalar(lhs, rhs) / lhs.len() / rhs.len();
    }

    static double angle(const Vector lhs, const Vector rhs)
    {
        return acos(cosBetween(lhs, rhs));
    }

    static bool areColiniar(const Vector lhs, const Vector rhs)
    {
        return 0 == vectorProduct(lhs, rhs);
    }

    static Vector getRandom(int l, int r)
    {
        Vector::coordinate_t x = Helpers::getRandom<Vector::coordinate_t>(l, r);
        Vector::coordinate_t y = Helpers::getRandom<Vector::coordinate_t>(l, r);
        return Vector(x, y);
    }
};