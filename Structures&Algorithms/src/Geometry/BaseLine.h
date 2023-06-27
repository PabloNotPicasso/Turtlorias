#pragma once

#include "Vector.h"

class BaseLine
{
public:
  double A;
  double B;
  double C;

public:
  BaseLine()
    : A(0)
    , B(0)
    , C(0)
  {}
  
  BaseLine(const double _A, const double _B, const double _C)
    : A(_A)
    , B(_B)
    , C(_C)
  {}
  
  BaseLine(const Point p1, const Point p2)
    : BaseLine(p1.y - p2.y, // A
               p2.x - p1.x, // B
               p2.y * p1.x - p1.y * p2.x // C
               )
  {}

  Vector directionVector() const{
    return {-B, A};
  }

  Vector normal() const{
    return {A, B};
  }

  double fun(const double x) const
  {
    return (-A * x - C)/B;
  }

  double evaluate(const Point p) const
  {
    return A*p.x + B*p.y + C;
  }

  bool belongs(const Point p) const
  {
    return 0 == evaluate(p);
  }

  bool areOnSameSide(const Point a, const Point b) const
  {
    double a_ev_sign = evaluate(a) > 0 ? 1 : -1;
    double b_ev_sign = evaluate(b) > 0 ? 1 : -1;
    return 1 == (a_ev_sign * b_ev_sign);
  }

  static BaseLine createByNormal(const Point p, const Vector norm)
  {
    BaseLine line;
    line.A = norm.x;
    line.B = norm.y;
    line.C = -line.A * p.x - line.B * p.y;
    return line;
  }

  static BaseLine createByDirection(const Point p, const Vector dir)
  {
    BaseLine line;
    line.A = -dir.y;
    line.B = dir.x;
    line.C = -line.A * p.x - line.B * p.y;
    return line;
  }

  static Point intersection(const BaseLine l1, const BaseLine l2)
  {
    double determ = l1.A*l2.B - l2.A*l1.B;
    double determ_x = -l1.C*l2.B + l2.C*l1.B;
    double determ_y = -l1.A*l2.C + l2.A*l1.C;
    return {determ_x/determ, determ_y/determ};
  }

  double distanceTo(const Point p)
  {
    if( A || B || C){
      return fabs( (p.x*A + p.y*B + C) / (sqrt(A*A + B*B) ) );
    }
    return p.distance();
  }
};

std::istream& operator>>(std::istream& is, BaseLine& line)
{
  is >> line.A >> line.B >> line.C;
  return is;
}

std::ostream& operator<<(std::ostream& os, const BaseLine line)
{
  os << "BaseLine { " << line.A << "x + " << line.B << "y + " << line.C << " }";
  return os;
}
