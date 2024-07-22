#ifndef EDGE_H
#define EDGE_H

#include <cmath>
#include <istream>
#include <ostream>
#include <iostream>

#include <boost/geometry.hpp>

#include "../point/point.h"

class edge { // edge
public:
  point begin, end;
  edge(point begin=point(), point end=point());

  bool get_intersection(const edge &line) const;
  bool point_on(const point &check_point) const;
  point operator|(const edge &line) const;

  friend std::ostream &operator<<(std::ostream &out, edge e);
  friend std::istream &operator>>(std::istream &inp, edge &e);
};

std::ostream &operator<<(std::ostream &out, edge e);
std::istream &operator>>(std::istream &inp, edge &e);

#endif
