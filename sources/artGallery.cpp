#include <cmath>
#include <unistd.h>

#include <boost/geometry.hpp>
#include <boost/geometry.hpp>

#include <SFML/Graphics.hpp>

#include "components/team/team.h"
#include "components/mpolygon/mpolygon.h"
#include "components/visualize/paper/paper.h"
#include "components/genetic_algorithm/genetic_algorithm.h"

typedef boost::geometry::model::d2::point_xy<double> point_type;
typedef boost::geometry::model::polygon<point_type> polygon_type;
typedef boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>> polygon;

int main() {
	// freopen("input.txt", "r", stdin);
	paper w;
	w.read_gallery();
	team t = w.read_team();
	w.draw_area(t);
	// std::cin >> gallery;
	// w.draw_gallery();
	// team t;
	// std::cin >> t;
	// w.draw_team(t);
	// w.draw_area(t);
}
