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
#include <boost/geometry/io/wkt/wkt.hpp>
#include <boost/geometry/algorithms/union.hpp>
#include <boost/geometry/algorithms/within.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/algorithms/covered_by.hpp>
#include <boost/geometry/strategies/cartesian/point_in_poly_franklin.hpp>

#include "team.h"
#include "../edge/edge.h"
#include "../guard/guard.h"
#include "../point/point.h"
#include "../mpolygon/mpolygon.h"

typedef boost::geometry::model::d2::point_xy<double> point_type;
typedef boost::geometry::model::polygon<point_type> polygon_type;
typedef boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>> polygon;

team::team(std::vector<guard> guards) : guards(guards) {
	size = guards.size();
	fit = calc_fit();
}
guard team::operator[](long long &position) {
	return guards[position];
}
void team::add(guard g) { // new guard
	guards.push_back(g);
	++size;
	fit = calc_fit();
}
void team::remove(long long &position) { // delete guard
	guards.erase(guards.begin() + position);
	--size;
	fit = calc_fit();
}
void team::change(guard g, long long &position) { // change guard
	guards[position] = g;
}
void team::calc_area() { // calc team visible zone/s
	visible_zones.clear();
	for (long long i = 0; i < size; ++i) {
		polygon poly;
		boost::geometry::read_wkt(guards[i].get_visible_zone().to_str(), poly);

		std::vector<polygon> upd_visible_zones;
		for (long long j = 0; j < visible_zones.size(); ++j) {
			std::vector<polygon> poly_union;

			boost::geometry::union_(poly, visible_zones[j], poly_union);
			
			if (poly_union.size() == 1) { // visible guard zone & past visible zone/s have union
				poly = poly_union[0];
			} else upd_visible_zones.push_back(visible_zones[j]);
		}

		visible_zones = upd_visible_zones;
		visible_zones.push_back(poly);
	}
}
double team::area() { // visible zone/s as number
	calc_area();

	double area = 0;
	for (const auto &i : visible_zones) area += boost::geometry::area(i);

	return area;
}
std::vector<polygon> team::polygons_area() { // visible zone/s as polygons
	calc_area();
	return visible_zones;
}
double team::calc_fit() {
	return area() / gallery.area() * 100;
}
team team::operator+(team &t) {
	long long gap = (std::rand() % (size - 1) + 1);
	team child;

	for (long long i = 0; i < gap; ++i) child.add(guards[i]);
	for (long long i = gap; i < size; ++i) child.add(t[i]);
	child.fit = child.calc_fit();

	return child;
}

std::istream &operator>>(std::istream &inp, team &t) {
	long long n;
	inp >> n;

	for (long long _i = 0; _i < n; ++_i) {
		double x, y;
		inp >> x >> y;

		t.add(guard(x, y, 1));
	}

	return inp;
}