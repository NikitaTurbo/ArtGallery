#ifndef MPOLYGON_H
#define MPOLYGON_H

#include <cmath>
#include <string>
#include <vector>
#include <iostream>

#include <boost/geometry.hpp>
#include <boost/geometry.hpp>
#include <boost/geometry/io/wkt/wkt.hpp>
#include <boost/geometry/algorithms/union.hpp>
#include <boost/geometry/algorithms/within.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/algorithms/covered_by.hpp>
#include <boost/geometry/strategies/cartesian/point_in_poly_franklin.hpp>

#include "../edge/edge.h"
#include "../point/point.h"

typedef boost::geometry::model::d2::point_xy<double> point_type;
typedef boost::geometry::model::polygon<point_type> polygon_type;
typedef boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>> polygon;

class mpolygon {
public:
  std::vector<point> points;
  long long size, md;
  double sum;

  mpolygon(std::vector<point> points = std::vector<point>(0, point()));
  void add(point p);
  std::string to_str();
  double area();
  polygon polygon_area();
  edge get_edge(long long num);
  bool point_in(point p);
  bool operator>(const mpolygon &pol2) const;
  mpolygon operator+(mpolygon &pol2);
  mpolygon operator*(mpolygon &pol2);
  point operator[](long long &position);

  friend std::ostream &operator<<(std::ostream &out, mpolygon p);
  friend std::istream &operator>>(std::istream &inp, mpolygon &e);
};

std::ostream &operator<<(std::ostream &out, mpolygon p);
std::istream &operator>>(std::istream &inp, mpolygon &e);

#endif