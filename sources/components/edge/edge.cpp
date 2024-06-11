#include <cmath>
#include <istream>
#include <ostream>
#include <iostream>

#include "edge.h"
#include "../point/point.h"

edge::edge(point begin, point end) : begin(begin), end(end) {}

bool edge::get_intersection(const edge &line) const {
	double cat1_x = end.x - begin.x;
	double cat1_y = end.y - begin.y;
	double cat2_x = line.end.x - line.begin.x;
	double cat2_y = line.end.y - line.begin.y;
	double prod1 = (cat1_x * (line.begin.y - begin.y)) - ((line.begin.x - begin.x) * cat1_y);
	double prod2 = (cat1_x * (line.end.y - begin.y)) - ((line.end.x - begin.x) * cat1_y);
	if (((prod1 < 0) && (prod2 < 0)) || ((prod1 > 0) && (prod2 > 0))) return false;

	prod1 = (cat2_x * (begin.y - line.begin.y)) - ((begin.x - line.begin.x) * cat2_y);
	prod2 = (cat2_x * (end.y - line.begin.y)) - ((end.x - line.begin.x) * cat2_y);
	if (((prod1 < 0) && (prod2 < 0)) || ((prod1 > 0) && (prod2 > 0))) return false;

	return true;
}
bool edge::pixel_on(const point &pixel) const { 
	return (std::round(((begin.y - end.y) * pixel.x + (end.x - begin.x) * pixel.y + (begin.x * end.y - end.x * begin.y))) == 0);
}
bool edge::pixel_on2(const point &pixel) const { // pixel on line
	edge self;
	self.begin = begin;
	self.end = end;
	return (self.pixel_on(pixel) && (((pixel.x <= begin.x && pixel.x >= end.x) || (pixel.x >= begin.x && pixel.x <= end.x)) && ((pixel.y <= begin.y && pixel.y >= end.y) || (pixel.y >= begin.y && pixel.y <= end.y))));
}
point edge::operator*(const edge &e2) const { // intersection
	edge e1 = *this;
	double u = ((e2.end.x - e2.begin.x) * (e1.begin.y - e2.begin.y) - (e2.end.y - e2.begin.y) * (e1.begin.x - e2.begin.x)) / ((e2.end.y - e2.begin.y) * (e1.end.x - e1.begin.x) - (e2.end.x - e2.begin.x) * (e1.end.y - e1.begin.y));

	point ans;
	ans.x = e1.begin.x + u * (e1.end.x - e1.begin.x);
	ans.y = e1.begin.y + u * (e1.end.y - e1.begin.y);

	return ans;
}

std::ostream &operator<<(std::ostream &out, edge e) {
	out << "1:" << e.begin << "2:" << e.end;
	return out;
}

std::istream &operator>>(std::istream &inp, edge &e) {
	inp >> e.begin >> e.end;
	return inp;
}