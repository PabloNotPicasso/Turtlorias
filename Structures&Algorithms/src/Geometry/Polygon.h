#pragma once

#include "BaseLine.h"
#include "Ray.h"
#include "Segment.h"

class Polygon
{
public:
  std::vector<Point> vertices;
  
  Polygon(std::vector<Point> vert)
    : vertices(vert)
  {}

  double area() const
  {
    double ans = 0;
    for( int idxCurrent = 0; idxCurrent < vertices.size(); ++idxCurrent)
    {
      int idxNext = (idxCurrent + 1) % vertices.size();
      Vector currentV({0,0}, vertices[idxCurrent]);
      Vector nextV({0,0}, vertices[idxNext]);

      ans += Vector::vectorProduct(currentV, nextV);
    }
    return fabs(ans) * 0.5;
  }

  bool isConvex() const
  {
    bool sameSign = true;
    
    Vector currentV(vertices[0], vertices[1]);
    Vector nextV(vertices[1], vertices[2]);

    double previousProd = Vector::vectorProduct(currentV, nextV);

    for(int idxCurrent = 1; sameSign && idxCurrent < vertices.size(); ++idxCurrent)
    {
      int idxNext = (idxCurrent + 1) % vertices.size();
      int idxNextNext = (idxNext + 1) % vertices.size();

      currentV = Vector(vertices[idxCurrent], vertices[idxNext]);
      nextV = Vector(vertices[idxNext], vertices[idxNextNext]);

      double currentProd = Vector::vectorProduct(currentV, nextV);

      sameSign = (currentProd >= 0 && previousProd >= 0) || 
                 (currentProd <= 0 && previousProd <= 0);

      previousProd = currentProd;
    }
    return sameSign;
  }

  bool belongs(const Point p)
  {
    if( isConvex() ) {
      return belongsConvex(p);
    } else {
      return belongsSimple(p);
    }
  }

private:
  bool belongsConvex(const Point p)
  {
    bool sameSign = true;
    int previousSign = 0;

    for(int idxCurrent = 0; sameSign && idxCurrent < vertices.size(); ++idxCurrent)
    {
      int idxNext = (idxCurrent + 1) % vertices.size();

      Vector currentV = Vector(p, vertices[idxCurrent]);
      Vector nextV = Vector(p, vertices[idxNext]);

      double currentProd = Vector::vectorProduct(currentV, nextV);

      sameSign = (currentProd >= 0 && previousSign >= 0) || 
                 (currentProd <= 0 && previousSign <= 0);

      previousSign = currentProd;
    }
    return sameSign;
  }

  bool belongsSimple(const Point p)
  {
    auto areIntersectedInDirection = [&]( Point directionP)
    {
      Ray ray;
      ray.start = p;
      ray.direction = directionP;

      // cout << "Ray: " << ray.start << " " << ray.direction << endl;

      int intersectionCnt = 0;
      for(int i = 0; i < vertices.size(); ++i)
      {
        int nextIdx = (i + 1) % vertices.size();
        bool isIntersected = Segment::areIntersected(Segment(vertices[i], vertices[nextIdx]), ray);
        intersectionCnt += isIntersected;

        if( isIntersected ){
          // cout << "is intersected with: " << Segment(vertices[i], vertices[nextIdx]) << endl;
        }
      }

      // cout << "Intersection cnt: " << intersectionCnt << endl;
      return intersectionCnt % 2 == 1;
    };

    bool ans = false;

    ans |= areIntersectedInDirection(Point::createRandomPoint());
    ans |= areIntersectedInDirection(-Point::createRandomPoint());
    ans |= areIntersectedInDirection(Point::createRandomPoint());
    ans |= areIntersectedInDirection(-Point::createRandomPoint());

    return ans;
  }
};

std::ostream& operator<<(std::ostream& os, const Polygon pol)
{
  os << "Polygon: [" << pol.vertices.size() << "]\n";
  for( auto i : pol.vertices )
    os << "\t(" << i.x << ", " << i.y << ")\n";
  return os;
}
