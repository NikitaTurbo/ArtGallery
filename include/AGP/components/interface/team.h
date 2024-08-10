#ifndef TEAM_H
#define TEAM_H

#include <cmath>
#include <vector>
#include <istream>
#include <iostream>

#include <boost/geometry.hpp>

#include "edge.h"
#include "guard.h"
#include "point.h"
#include "mpolygon.h"

typedef boost::geometry::model::d2::point_xy<double> point_type;
typedef boost::geometry::model::polygon<point_type> polygon_type;
typedef boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>> polygon;

class team {
private:
  std::vector<guard> guards;
  std::vector<polygon> visible_zones;
public:
  double fit;
  long long size;

  team(std::vector<guard> guards=std::vector<guard> (0, guard(0, 0)));
  guard operator[](long long &position);
  void add(guard g);
  void remove(long long &position);
  void change(guard g, long long &position);
  void calc_area();
  double area();
  std::vector<polygon> polygons_area();
  double calc_fit();
  team operator+(team &t);

  friend std::istream &operator>>(std::istream &inp, team &t);
};

std::istream &operator>>(std::istream &inp, team &t);

#endif
