#include <cmath>
#include <istream>
#include <ostream>
#include <iostream>

#include <AGP/components/interface/point.h>

double round(const double &x, const long long &n) {
	return std::round(x * std::pow(10, n)) / std::pow(10, n); 
}

point::point(double x, double y, double zero_x, double zero_y, long long f) : x(x), y(y), zero_x(zero_x), zero_y(zero_y), f(f) {}

point point::operator~() {
	x = round(x, 6);
	y = round(y, 6);
	return (*this);
}
point point::real() const {
	return point(x - zero_x, y - zero_y);
}
double point::dist() const {
	return std::sqrt(x * x + y * y);
}
double point::real_dist() const {
	return real().dist();
}
bool point::operator>(const point &p) const {
	if (f == 1) {
		return real_dist() > p.real_dist();
	} else {
		return dist() > p.dist();
	}
}
bool point::operator<(const point &p) const {
	if (f == 1) {
		return real_dist() < p.real_dist();
	} else {	
		return dist() < p.dist();
	}
}
bool point::operator<=(const point &p) const {
	if (f == 1) {
		return real_dist() <= p.real_dist();
	} else {
		return dist() <= p.dist();
	}
}
bool point::operator==(const point &p) const {
	if (f == 1) {
		return real_dist() == p.real_dist();
	} else {
		return dist() == p.dist();
	}
}
bool point::operator!=(const point &p) const {
	if (f == 1) {
		return real_dist() != p.real_dist();
	} else {
		return dist() != p.dist();
	}
}
bool point::operator>=(const point &p) const {
	if (f == 1) {
		return real_dist() >= p.real_dist();
	} else {
		return dist() >= p.dist();
	}
}
void point::zero(double x, double y) {
	zero_x = x;
	zero_y = y;
}
point point::mid(const point &p) const {
	return point((x + p.x) / 2, (y + p.y) / 2);
}
void point::flag(long long new_f) {
	f = new_f;
}

std::ostream &operator<<(std::ostream &out, point p) {
	out << p.x << ' ' << p.y << "\n";
	return out;
}

std::istream &operator>>(std::istream &inp, point &p) {
	inp >> p.x >> p.y;
	return inp;
}