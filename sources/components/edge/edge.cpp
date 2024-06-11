#include <cmath>
#include <istream>
#include <ostream>
#include <iostream>

#include "edge.h"
#include "../point/point.h"

edge::edge(point p0, point p1) : p0(p0), p1(p1) {}

bool edge::get_intersection(const edge &line) const {
	double cat1_x = p1.x - p0.x;
	double cat1_y = p1.y - p0.y;
	double cat2_x = line.p1.x - line.p0.x;
	double cat2_y = line.p1.y - line.p0.y;
	double prod1 = (cat1_x * (line.p0.y - p0.y)) - ((line.p0.x - p0.x) * cat1_y);
	double prod2 = (cat1_x * (line.p1.y - p0.y)) - ((line.p1.x - p0.x) * cat1_y);
	if (((prod1 < 0) && (prod2 < 0)) || ((prod1 > 0) && (prod2 > 0))) return false;

	prod1 = (cat2_x * (p0.y - line.p0.y)) - ((p0.x - line.p0.x) * cat2_y);
	prod2 = (cat2_x * (p1.y - line.p0.y)) - ((p1.x - line.p0.x) * cat2_y);
	if (((prod1 < 0) && (prod2 < 0)) || ((prod1 > 0) && (prod2 > 0))) return false;

	return true;
}
bool edge::pixel_on(const point &pixel) const { 
	return (std::round(((p0.y - p1.y) * pixel.x + (p1.x - p0.x) * pixel.y + (p0.x * p1.y - p1.x * p0.y))) == 0);
}
bool edge::pixel_on2(const point &pixel) const { // pixel on line
	edge self;
	self.p0 = p0;
	self.p1 = p1;
	return (self.pixel_on(pixel) && (((pixel.x <= p0.x && pixel.x >= p1.x) || (pixel.x >= p0.x && pixel.x <= p1.x)) && ((pixel.y <= p0.y && pixel.y >= p1.y) || (pixel.y >= p0.y && pixel.y <= p1.y))));
}
point edge::operator*(const edge &e2) const { // intersection
	edge e1 = *this;
	double u = ((e2.p1.x - e2.p0.x) * (e1.p0.y - e2.p0.y) - (e2.p1.y - e2.p0.y) * (e1.p0.x - e2.p0.x)) / ((e2.p1.y - e2.p0.y) * (e1.p1.x - e1.p0.x) - (e2.p1.x - e2.p0.x) * (e1.p1.y - e1.p0.y));

	point ans;
	ans.x = e1.p0.x + u * (e1.p1.x - e1.p0.x);
	ans.y = e1.p0.y + u * (e1.p1.y - e1.p0.y);

	return ans;
}

std::ostream &operator<<(std::ostream &out, edge e) {
	out << "1:" << e.p0 << "2:" << e.p1;
	return out;
}

std::istream &operator>>(std::istream &inp, edge &e) {
	inp >> e.p0 >> e.p1;
	return inp;
}