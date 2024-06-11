#ifndef POINT_H
#define POINT_H

#include <cmath>
#include <istream>
#include <ostream>
#include <iostream>

double round(const double &x, const long long &n);

class point {
private:
  long long f;
  double zero_x, zero_y;
public:
  double x, y;

  point(double x=0.0, double y=0.0, double zero_x=0.0, double zero_y=0.0, long long f=0);

  point operator~();
  point real() const;
  double dist() const;
  double real_dist() const;
  bool operator>(const point &p) const;
  bool operator<(const point &p) const;
  bool operator<=(const point &p) const;
  bool operator==(const point &p) const;
  bool operator>=(const point &p) const;

  void zero(double x=0.0, double y=0.0);
  point mid(const point &p) const;
  void flag(long long new_f=0);

  friend std::ostream& operator<<(std::ostream& out, point p);
  friend std::istream& operator>>(std::istream& inp, point& p);
};

std::ostream &operator<<(std::ostream &out, point p);
std::istream &operator>>(std::istream &inp, point &p);

#endif