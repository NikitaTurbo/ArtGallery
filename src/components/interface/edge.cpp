#include <cmath>
#include <istream>
#include <ostream>
#include <iostream>
#include <vector>

#include <boost/geometry.hpp>

#include <AGP/components/interface/edge.h>
#include <AGP/components/interface/point.h>

typedef boost::geometry::model::d2::point_xy<double> point_type;
typedef boost::geometry::model::segment<point_type> segment;

edge::edge(point begin, point end) : begin(begin), end(end) {}

bool edge::get_intersection(const edge &line) const {
	point_type this_begin(begin.x, begin.y), this_end(end.x, end.y);
	point_type line_begin(line.begin.x, line.begin.y), line_end(line.end.x, line.end.y);

	return boost::geometry::intersects(segment(this_begin, this_end), segment(line_begin, line_end));
}

bool edge::point_on(const point &check_point) const {
	point_type check_point_type(check_point.x, check_point.y);
	point_type this_begin(begin.x, begin.y), this_end(end.x, end.y);
	
	return (boost::geometry::distance(check_point_type, this_begin) + boost::geometry::distance(check_point_type, this_end)) == boost::geometry::distance(this_begin, this_end);
}

point edge::operator|(const edge &line) const {
	std::vector<point_type> intersection_points;

	point_type this_begin(begin.x, begin.y), this_end(end.x, end.y);
	point_type line_begin(line.begin.x, line.begin.y), line_end(line.end.x, line.end.y);

	boost::geometry::intersection(segment(this_begin, this_end), segment(line_begin, line_end), intersection_points);
	
	if (!intersection_points.empty()) {
		return point(intersection_points[0].x(), intersection_points[0].y());
	}
	return point(0, 0);
}

std::ostream &operator<<(std::ostream &out, edge e) {
	out << "1:" << e.begin << " 2:" << e.end;
	return out;
}

std::istream &operator>>(std::istream &inp, edge &e) {
	inp >> e.begin >> e.end;
	return inp;
}