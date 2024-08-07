#ifndef VIEW_H
#define VIEW_H

#include <cmath>
#include <vector>

#include <boost/geometry.hpp>

#include <SFML/Graphics.hpp>

#include <AGP/components/interface/edge.h>
#include <AGP/components/interface/team.h>
#include <AGP/components/interface/guard.h>
#include <AGP/components/interface/point.h>
#include <AGP/components/interface/mpolygon.h>

typedef boost::geometry::model::d2::point_xy<double> point_type;
typedef boost::geometry::model::polygon<point_type> polygon_type;
typedef boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>> polygon;

double read_x(double x);
double read_y(double y, long long width);
double draw_x(double x);
double draw_y(double y, long long width);

class view {
private:
	sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(800, 800), "ArtGallery");
	std::vector<sf::CircleShape> points;
	std::vector<sf::VertexArray> polygons;
	sf::VertexArray room = sf::VertexArray(sf::LineStrip);
public:
	view(long long height=800, long long width=800);

	void read_gallery();
	void draw_gallery();
	team read_team();
	void draw_team(team &t);
	void draw_area(team &t);
};

#endif