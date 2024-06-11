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

#include "components/edge/edge.h"
#include "components/team/team.h"
#include "components/guard/guard.h"
#include "components/point/point.h"
#include "components/mpolygon/mpolygon.h"
#include "components/visualize/paper/paper.h"
#include "components/genetic_algorithm/genetic_algorithm.h"

typedef boost::geometry::model::d2::point_xy<double> point_type;
typedef boost::geometry::model::polygon<point_type> polygon_type;
typedef boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>> polygon;

int main() {
	// paper w;
	// w.read_gallery();
	// team t = w.read_team();
	// w.draw_area(t);
	edge e = edge(point(1, 1), point (7, 8));
	std::cout << e * (edge(point(4, 0), point(4, 10000))) << std::endl;
}