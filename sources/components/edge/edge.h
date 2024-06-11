#ifndef EDGE_H
#define EDGE_H

#include <cmath>
#include <istream>
#include <ostream>
#include <iostream>

#include "../point/point.h"

class edge { // edge
public:
  point p0;
  point p1;
  edge(point p0=point(), point p1=point());

  bool get_intersection(const edge &line) const;
  bool pixel_on(const point &pixel) const;
  bool pixel_on2(const point &pixel) const;
  point operator*(const edge &e2) const;

  friend std::ostream &operator<<(std::ostream &out, edge e);
  friend std::istream &operator>>(std::istream &inp, edge &e);
};

std::ostream &operator<<(std::ostream &out, edge e);
std::istream &operator>>(std::istream &inp, edge &e);

#endif