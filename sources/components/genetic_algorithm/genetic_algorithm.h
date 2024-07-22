#ifndef GENALG_H
#define GENALG_H

#include <map>
#include <set>
#include <cmath>
#include <string>
#include <vector>
#include <istream>
#include <ostream>
#include <iostream>
#include <algorithm>

#include <boost/geometry.hpp>
#include <boost/geometry.hpp>

#include <SFML/Graphics.hpp>

#include "../edge/edge.h"
#include "../team/team.h"
#include "../guard/guard.h"
#include "../point/point.h"
#include "../mpolygon/mpolygon.h"
#include "../visualize/paper/paper.h"

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