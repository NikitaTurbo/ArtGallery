#ifndef GENALG_H
#define GENALG_H

#include <cmath>
#include <vector>

#include <boost/geometry.hpp>

#include <SFML/Graphics.hpp>

#include "../ui/view.h"
#include "edge.h"
#include "team.h"
#include "guard.h"
#include "point.h"
#include "mpolygon.h"

typedef boost::geometry::model::d2::point_xy<double> point_type;
typedef boost::geometry::model::polygon<point_type> polygon_type;
typedef boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>> polygon;

point random_point();
long long random_of_range(long long l, long long r);
bool cmp(team a, team b);

class population {
private:
	std::vector<team> populate;
public:
	long long n, m;

	population(long long n, long long m);
	void update();
	team get();
};

#endif
