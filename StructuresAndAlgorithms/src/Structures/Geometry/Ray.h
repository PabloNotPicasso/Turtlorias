#pragma once

#include "BaseLine.h"

class Ray {
public:
    Point start;
    Point direction;

    bool belongs(const Point p) const
    {
        Vector v1(start, direction);
        Vector v2(start, p);

        return (0 == Vector::vectorProduct(v1, v2)) &&
            // scalar between (start, p) and (start, direction) should be >=0 cause angle is ~0*
            (Vector::scalar(v1, v2) >= 0);
    }

    double distanceTo(const Point p) const
    {
        Vector directionVec(start, direction);
        Vector toPoint(start, p);

        bool isProjected = Vector::scalar(directionVec, toPoint) >= 0;

        if (!isProjected) {
            return Point::distance(p, start);
        }
        // hipotenusa * sinus
        return toPoint.len() * fabs(Vector::sinBetween(directionVec, toPoint));
    }
};
