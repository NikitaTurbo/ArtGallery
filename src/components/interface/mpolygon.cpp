#include "boost/geometry/algorithms/detail/intersection/interface.hpp"
#include <cmath>
#include <string>
#include <vector>
#include <istream>
#include <ostream>
#include <iostream>

#include <boost/geometry.hpp>

#include <AGP/components/interface/edge.h>
#include <AGP/components/interface/point.h>
#include <AGP/components/interface/mpolygon.h>

typedef boost::geometry::model::d2::point_xy<double> point_type;
typedef boost::geometry::model::polygon<point_type> polygon;
typedef boost::geometry::model::segment<point_type> segment;

mpolygon::mpolygon(std::vector<point> points) : points(points) {
	size = points.size();
	for (const auto &i : points) sum += i.x + i.y;
}

void mpolygon::add(point p) {
	points.push_back(p);
	sum += p.x + p.y;
	++size;
}
std::string mpolygon::to_polygon() {
	std::string str = "POLYGON((";

	for (long long i = 0; i < size; ++i) str += std::to_string(points[i].x) + ' ' + std::to_string(points[i].y) + ',';

	str += std::to_string(points[0].x) + ' ' + std::to_string(points[0].y);
	str += "))";

	return str;
}
double mpolygon::area() {
	polygon poly;
	boost::geometry::read_wkt(to_polygon(), poly);

	return boost::geometry::area(poly);
}
polygon mpolygon::polygon_area() {
	polygon poly;
	boost::geometry::read_wkt(to_polygon(), poly);

	return poly;
}
edge mpolygon::get_edge(long long num) {
	return edge(points[num], points[(num + 1) % points.size()]);
}
bool mpolygon::point_in(point p) {
	point_type p2(p.x, p.y);
	
	bool is_inside = boost::geometry::covered_by(p2, polygon_area());

	if (!is_inside) {
		for (long long i = 0; i < size; ++i) {
			edge e = get_edge(i);
			if (e.point_on(p)) {
				return true;
			}
		}
	}
	return is_inside;
}
bool mpolygon::operator>(const mpolygon &pol2) const {
	return sum > pol2.sum;
}
mpolygon mpolygon::operator+(mpolygon &pol2) {
	return (*this);
}
mpolygon mpolygon::operator*(mpolygon &pol2) {
	return pol2;
}
point mpolygon::operator[](long long &position) {
	return points[position];
}
std::ostream &operator<<(std::ostream &out, mpolygon p) {
	for (long long i = 0; i < p.size; ++i) out << p.points[i];
	return out;
}

std::istream &operator>>(std::istream &inp, mpolygon &e) {
  double y;
	std::string str;

	inp >> str;

	while (str != ";") {
		inp >> y;

		e.add(point(std::stoll(str), y));

		inp >> str;
	}

	long long j = (e.size - 1);
	for (long long i = 0; i < e.size; ++i) {
		e.sum += e.points[i].x;
		e.sum += e.points[i].y;
		j = i;
	}

	return inp;
}