#pragma once

#include "Ray.h"

class Segment
{
public:
  Point start;
  Point end;

  Segment() = default;
  Segment(const Point _start, const Point _end)
    : start(_start)
    , end(_end)
  {}

  bool belongs(const Point p) const
  {
    Vector start_to_p(start, p);
    Vector end_to_p(end, p);

    return (0 == Vector::vectorProduct(start_to_p, end_to_p)) &&
          // scalar between (start, p) and (end, p) should be -1 cause angle is ~180*
           (Vector::scalar(start_to_p, end_to_p) <= 0);
  }

  double distanceTo(const Point p) const
  {
    if( belongs(p) ){
      return 0;
    }
    Vector start_to_end(start, end);
    Vector start_to_p(start, p);
    Vector end_to_p(end, p);

    if ( Vector::scalar(start_to_end, start_to_p) < 0 )
    {
      return Point::distance(p, start);
    }
    if ( Vector::scalar(-start_to_end, end_to_p) < 0 )
    {
      return Point::distance(p, end);
    }
    // hipotenusa * sinus
    return start_to_p.len() * fabs( Vector::sinBetween(start_to_end, start_to_p) );
  }

  static bool areIntersected(const Segment a, const Segment b)
  {
    Vector aVec(a.start, a.end);
    Vector bVec(b.start, b.end);

    bool areOnDifferentSides =
      Vector::vectorProduct(aVec, Vector(a.start, b.start)) * Vector::vectorProduct(aVec, Vector(a.start, b.end)) < 0;
    areOnDifferentSides &=
      Vector::vectorProduct(bVec, Vector(b.start, a.start)) * Vector::vectorProduct(bVec, Vector(b.start, a.end)) < 0;

    bool belongToEachOther =  a.belongs(b.start) || 
                              a.belongs(b.end) || 
                              b.belongs(a.start) || 
                              b.belongs(a.end);

    return areOnDifferentSides || belongToEachOther;
  }

  static bool areIntersected(const Segment a, const Ray ray)
  {
    Vector rayVec(ray.start, ray.direction);

    bool pointsAreOnDifferentSides =
      Vector::vectorProduct(rayVec, Vector(ray.start, a.start)) * Vector::vectorProduct(rayVec, Vector(ray.start, a.end)) < 0;

    bool angleCheck = Vector::scalar(Vector(ray.start, ray.direction), Vector(ray.start, a.start) ) > 0 &&
    Vector::scalar(Vector(ray.start, ray.direction), Vector(ray.start, a.end) ) > 0;

    bool belongToEachOther =  a.belongs(ray.start) || ray.belongs(a.start) || ray.belongs(a.end);

    return (pointsAreOnDifferentSides && angleCheck) || belongToEachOther;
  }

  static double distance(const Segment a, const Segment b)
  {
    if( areIntersected(a,b) ){
      return 0;
    }
    double ans = a.distanceTo(b.start);
    ans = std::min( ans, a.distanceTo(b.end));
    ans = std::min( ans, b.distanceTo(a.start));
    ans = std::min( ans, b.distanceTo(a.end));
    return ans;
  }
};

std::ostream& operator<<(std::ostream& os, const Segment seg)
{
  os << "Segment[" << seg.start << ", " << seg.end << "]";
  return os;
}
