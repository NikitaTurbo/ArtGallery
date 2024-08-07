#ifndef GUARD_H
#define GUARD_H

#include <map>
#include <set>
#include <vector>

#include <boost/geometry.hpp>

#include "edge.h"
#include "point.h"
#include "mpolygon.h"

double random_f();

extern mpolygon gallery;

class guard {
private:
  mpolygon visible_zone;

public:
  double x, y;

  guard(double x=0.0, double y=0.0, long long stc=1);
  bool operator<(const guard &g) const;
  mpolygon get_visible_zone();
  void set_visible_zone(mpolygon poly);

  friend std::ostream &operator<<(std::ostream &out, guard g);
  friend std::istream &operator>>(std::istream &inp, guard &g);
};

std::ostream &operator<<(std::ostream &out, guard g);
std::istream &operator>>(std::istream &inp, guard &g);

#endif