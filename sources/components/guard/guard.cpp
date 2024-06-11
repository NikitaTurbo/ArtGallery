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
#include <boost/geometry/io/wkt/wkt.hpp>
#include <boost/geometry/algorithms/union.hpp>
#include <boost/geometry/algorithms/within.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/algorithms/covered_by.hpp>
#include <boost/geometry/strategies/cartesian/point_in_poly_franklin.hpp>

#include "guard.h"
#include "../edge/edge.h"
#include "../point/point.h"
#include "../mpolygon/mpolygon.h"

typedef boost::geometry::model::d2::point_xy<double> point_type;
typedef boost::geometry::model::polygon<point_type> polygon_type;
typedef boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>> polygon;

double random_f() {
    double x = (std::rand() % 19999) - 1e4;
    double y = (std::rand() % 19999) - 1e4;

    return x + y / 1e4;
}

std::set<std::pair<double, double>> save_be;
std::map<std::pair<double, double>, mpolygon> save;
mpolygon gallery; // gallery

guard::guard(double x, double y, long long stc) : x(x), y(y) {
	if (stc == 1) {
		if (save_be.find({x, y}) != save_be.end()) visible_zone = save[{x, y}];
		else {
			edge edges;
			std::vector<std::vector<point>> points(gallery.size, std::vector<point> (0, point()));

			for (long long i = 0; i < gallery.size; ++i) {
				std::vector<std::pair<point, long long>> now_points;
				edges = edge(point(x, y), point(x + (gallery[i].x - x) * 1e4, y + (gallery[i].y - y) * 1e4));
				long long jj = (gallery.size - 1);

				for (long long ii = 0; ii < gallery.size; ++ii) {
					if (edges.get_intersection(edge(gallery[jj], gallery[ii]))) {
						if (((edges * edge(gallery[jj], gallery[ii])).x / (edges * edge(gallery[jj], gallery[ii])).x == 1) || ((edges * edge(gallery[jj], gallery[ii])).x == 0)) {
							point p = (edges * edge(gallery[jj], gallery[ii]));

							now_points.push_back({~p, jj});
							now_points[(now_points.size() - 1)].first.flag(1);
							now_points[(now_points.size() - 1)].first.zero(x, y);
						} else {
							now_points.push_back({gallery[jj], jj});
							now_points[(now_points.size() - 1)].first.flag(1);
							now_points[(now_points.size() - 1)].first.zero(x, y);

							now_points.push_back({gallery[ii], jj});
							now_points[(now_points.size() - 1)].first.flag(1);
							now_points[(now_points.size() - 1)].first.zero(x, y);
						}
					}
					jj = ii;
				}
				std::sort(now_points.begin(), now_points.end());
				if (now_points.size() > 0) {
					now_points[0].first.zero(gallery[now_points[0].second].x, gallery[now_points[0].second].y);
					points[now_points[0].second].push_back(now_points[0].first);
				}

				for (long long ii = 1; ii < now_points.size(); ++ii) {
					if (!gallery.point_in(now_points[ii - 1].first.mid(now_points[ii].first))) break;

					now_points[ii].first.zero(gallery[now_points[ii].second].x, gallery[now_points[ii].second].y);
					points[now_points[ii].second].push_back(~now_points[ii].first);
				}
			}

			std::vector<point> new_points;
			long long b = 0;
			for (long long i = 0; i < gallery.size; ++i) {
				std::sort(points[i].begin(), points[i].end());

				for (long long j = 0; j < points[i].size(); ++j) {
					~points[i][j];
					if (new_points.size() == 0) new_points.push_back(points[i][j]);
					else {
						if ((points[i][j].x != new_points[new_points.size() - 1].x) || (points[i][j].y != new_points[new_points.size() - 1].y)) {
							if ((points[i][j].x == new_points[0].x) && (points[i][j].y == new_points[0].y)) {
								b = 1;
								break;
							}

							new_points.push_back(~points[i][j]);
						}
					}
				}

				if (b == 1) break;
			}

			visible_zone = mpolygon(new_points);

			save_be.insert({x, y});
			save[{x, y}] = visible_zone;
		}
	}
}
bool guard::operator<(const guard &g2) const {
	return ((x + y) < (g2.x + g2.y));
}
mpolygon guard::get_visible_zone() {
	return visible_zone;
}
void guard::set_visible_zone(mpolygon poly) {
	visible_zone = poly;
}

std::ostream &operator<<(std::ostream &out, guard g) {
	out << g.x << ' ' << g.y << ' ' << g.get_visible_zone();
	return out;
}

std::istream &operator>>(std::istream &inp, guard &g) {
	double x, y;
	inp >> x >> y;

	g = guard(x, y, 1);

	return inp;
}