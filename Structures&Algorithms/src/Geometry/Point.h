#pragma once

class Point {
public:
    double x, y;

    Point()
        : x(0)
        , y(0)
    {
    }

    Point(const double _x, const double _y)
        : x(_x)
        , y(_y)
    {
    }

    Point operator-() const
    {
        return {-x, -y};
    }

    double distance() const
    {
        return sqrt(x * x + y * y);
    }

    static double distance(const Point a, const Point b)
    {
        double x = b.x - a.x;
        double y = b.y - a.y;
        return sqrt(x * x + y * y);
    }

    static Point createRandomPoint()
    {
        double x = rand() % 5000;
        double y = rand() % 5000;

        return {x / 10, y / 10};
    }
};

std::istream& operator>>(std::istream& is, Point& p)
{
    is >> p.x >> p.y;
    return is;
}

std::ostream& operator<<(std::ostream& os, const Point p)
{
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}
