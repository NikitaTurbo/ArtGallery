#include <map>
#include <set>
#include <cmath>
#include <string>
#include <vector>
#include <istream>
#include <ostream>
#include <iostream>
#include <unistd.h>
#include <algorithm>

#include <boost/geometry.hpp>
#include <boost/geometry.hpp>
#include <boost/geometry/io/wkt/wkt.hpp>
#include <boost/geometry/algorithms/union.hpp>
#include <boost/geometry/algorithms/within.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/algorithms/covered_by.hpp>
#include <boost/geometry/strategies/cartesian/point_in_poly_franklin.hpp>

#include <SFML/Graphics.hpp>

#include "../edge/edge.h"
#include "../team/team.h"
#include "../guard/guard.h"
#include "../point/point.h"
#include "genetic_algorithm.h"
#include "../mpolygon/mpolygon.h"
#include "../visualize/paper/paper.h"

typedef boost::geometry::model::d2::point_xy<double> point_type;
typedef boost::geometry::model::polygon<point_type> polygon_type;
typedef boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>> polygon;

point random_point() { // random point of gallery
  point p1, p2, p3;
	std::vector<point> g;
  double alpha, beta, gyama, new_x, new_y;
  long long  rand_vertex;
	long long number_of_vertex = gallery.points.size();
	do {
		rand_vertex = std::rand() % (number_of_vertex - 1);
		p1 = gallery.points[rand_vertex % number_of_vertex];
		p2 = gallery.points[(rand_vertex + 1) % number_of_vertex];
		p3 = gallery.points[(rand_vertex + 2) % number_of_vertex];

		alpha = (std::rand() % 100) / 100.0;
		beta = (std::rand() % ((long long)((1 - alpha) * 100))) / 100.0;
		gyama = 1 - alpha - beta;

		new_x = alpha * p1.x + beta * p2.x + gyama * p3.x;
		new_y = alpha * p1.y + beta * p2.y + gyama * p3.y;
		g.push_back(point(new_x, new_y));
	} while (!gallery.point_in(point(new_x, new_y)));

	return point(new_x, new_y);
}
long long random_of_range(long long l, long long r) {
	return l + (std::rand() % (r - l + 1));
}

bool cmp(team a, team b) {
	if (a.fit == b.fit) return a.size > b.size;
	return a.fit < b.fit;
}

population::population(long long n, long long m) : n(n), m(m) {
	for (long long _i = 0; _i < m; ++_i) {
		team t;
		for (long long _j = 0; _j < random_of_range(gallery.size / 2, gallery.size); ++_j) {
			point guard_point = random_point();
			t.add(guard(guard_point.x, guard_point.y, 1));
		}

		populate.push_back(t);
	}
}
void population::update() {
	std::sort(populate.begin(), populate.end(), cmp);

	team bmx = populate[m - 1]; // best max fit
	team smx = populate[m - 2]; // 2 best max fit

	populate[0] = bmx + smx;
	if (std::rand() % 10 == 0) {
		long long ind = (std::rand() % (populate[0].size - 1) + 1);
		point guard_point = random_point();
		populate[0].change(guard(guard_point.x, guard_point.y, 1), ind);
	}
}

team population::get() {
	return populate[m - 1];
}