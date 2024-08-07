#include <cmath>
#include <vector>
#include <istream>
#include <ostream>
#include <iostream>

#include <boost/geometry.hpp>

#include <AGP/components/interface/edge.h>
#include <AGP/components/interface/guard.h>
#include <AGP/components/interface/point.h>
#include <AGP/components/interface/mpolygon.h>

typedef boost::geometry::model::d2::point_xy<double> point_type;
typedef boost::geometry::model::polygon<point_type> polygon;
typedef boost::geometry::model::segment<point_type> segment;
	
double random_f() {
    double x = (std::rand() % 19999) - 1e4;
    double y = (std::rand() % 19999) - 1e4;

    return (x + y) / 1e4;
}

mpolygon gallery; // gallery

guard::guard(double x, double y, long long stc) : x(x), y(y) {
	/* Visibility point algorithm:
		Step 1: Draw rays and their intersections.
		Step 2: Frind cross/touch points of intersections.
		Step 3: Sort intersections on a ray by their distances from the guard. Find visible/invisible points of sorted intersections.
		Step 4: Sort visible points by all edges of polygon. 
	*/	
	std::vector<point> visible_points;
    for (long long ind_corner = 0; ind_corner < gallery.size; ++ind_corner) {
    	std::vector<std::pair<point, bool>> ray;
    	point corner = gallery[ind_corner];
		edge visible = edge(point(x, y), point(x + (corner.x - x) * 1e4, y + (corner.y - y) * 1e4));
		edge to_corner = edge(point(x, y), corner);

		long long ind_previous = (gallery.size - 1);
		for (long long ind_now = 0; ind_now < gallery.size; ++ind_now) { // Find intersections from guard to all corners & all edges of polygon
			edge now = edge(gallery[ind_previous], gallery[ind_now]);
					
			if (visible.get_intersection(now)) {
				point intersection = visible | now;

				bool is_cross = !gallery.point_in(point(intersection.x + (corner.x - x) * 2e-2, intersection.y + (corner.y - y) * 2e-2)); // Check cross/touch point
				
				ray.push_back({intersection, is_cross});
			}

			ind_previous = ind_now;
		}

		if (ray.size() > 0) {
			point_type guard(x, y);
			std::sort(ray.begin(), ray.end(), [&guard](const std::pair<point, bool> &a, const std::pair<point, bool> &b) { // Sort ray points of their distance to guard
				point_type point_a(a.first.x, a.first.y), point_b(b.first.x, b.first.y);

    		    return boost::geometry::distance(guard, point_a) < boost::geometry::distance(guard, point_b);
			});
			
			bool is_cross = false;
			for (const auto &ray_point : ray) { // Find in ray visible points
				if (!is_cross) visible_points.push_back(ray_point.first);
				else break;
				
				is_cross = ray_point.second;
			}
		}
    }
    
    std::vector<point> polygon_points;  // Sort by all edges of polygon
    long long ind_previous = (gallery.size - 1);
	for (long long ind_now = 0; ind_now < gallery.size; ++ind_now) {
		edge now = edge(gallery[ind_previous], gallery[ind_now]);

		std::vector<point> on_edge_points;
		for (const auto &visible_point : visible_points) {
			if (now.point_on(visible_point)) on_edge_points.push_back(visible_point);
		}
		
		point_type left_corner(gallery[ind_previous].x, gallery[ind_previous].y);
		std::sort(on_edge_points.begin(), on_edge_points.end(), [&left_corner](const point &a, const point &b) {
			point_type point_a(a.x, a.y), point_b(b.x, b.y);

    		return boost::geometry::distance(left_corner, point_a) < boost::geometry::distance(left_corner, point_b);
		});
		
		for (const auto &on_edge_point : on_edge_points) polygon_points.push_back(on_edge_point);
		
		ind_previous = ind_now;
	}
	
	visible_zone = mpolygon(polygon_points);
}
bool guard::operator<(const guard &g) const {
	return ((x + y) < (g.x + g.y));
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