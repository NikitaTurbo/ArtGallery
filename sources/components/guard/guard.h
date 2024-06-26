#ifndef GUARD_H
#define GUARD_H

#include <map>
#include <set>
#include <vector>
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
#include "../mpolygon/mpolygon.h"

// typedef boost::geometry::model::d2::point_xy<double> point_type;
// typedef boost::geometry::model::polygon<point_type> polygon_type;
// typedef boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>> polygon;

double random_f();

extern std::set<std::pair<double, double>> save_be;
extern std::map<std::pair<double, double>, mpolygon> save;
extern mpolygon gallery;

class guard {
private:
  mpolygon visible_zone;

public:
  double x, y;

  guard(double x=0.0, double y=0.0, long long stc=1);
  bool operator<(const guard &g2) const;
  mpolygon get_visible_zone();
  void set_visible_zone(mpolygon poly);

  friend std::ostream &operator<<(std::ostream &out, guard g);
  friend std::istream &operator>>(std::istream &inp, guard &g);
};

std::ostream &operator<<(std::ostream &out, guard g);
std::istream &operator>>(std::istream &inp, guard &g);

#endif