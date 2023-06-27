#pragma once

#include "Point.h"

class Vector {
public:
    double x, y;

public:
    Vector()
        : x(0)
        , y(0)
    {
    }

    Vector(const double start, const double end)
        : x(start)
        , y(end)
    {
    }

    Vector(const Point start, const Point end)
        : x(end.x - start.x)
        , y(end.y - start.y)
    {
    }

    Vector operator-() const
    {
        return Vector(-x, -y);
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
};

std::ostream& operator<<(std::ostream& os, const Vector v)
{
    os << "Vector(" << v.x << ", " << v.y << ")";
    return os;
}

std::istream& operator>>(std::istream& is, Vector& v)
{
    is >> v.x >> v.y;
    return is;
}

Vector operator+(const Vector lhs, const Vector rhs)
{
    return {lhs.x + rhs.x, lhs.y + rhs.y};
}

Vector operator-(const Vector lhs, const Vector rhs)
{
    return {lhs.x - rhs.x, lhs.y - rhs.y};
}