#include <cmath>
#include <vector>
#include <unistd.h>

#include <boost/geometry.hpp>
#include <boost/geometry.hpp>

#include <SFML/Graphics.hpp>

#include "paper.h"
#include "../../team/team.h"
#include "../../guard/guard.h"
#include "../../point/point.h"
#include "../../mpolygon/mpolygon.h"

typedef boost::geometry::model::d2::point_xy<double> point_type;
typedef boost::geometry::model::polygon<point_type> polygon_type;
typedef boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double>> polygon;

double read_x(double x) {
	return x / 50 - 1;
}
double read_y(double y, long long width) {
	return (width - y) / 50 - 1;
}
double draw_x(double x) {
	return (x + 1) * 50;
}
double draw_y(double y, long long width) {
	return width - (y + 1) * 50;
}

paper::paper(long long height, long long width) {
	window.setSize(sf::Vector2u(height, width));
}

void paper::read_gallery() {
	long long ind = 0;
  bool isEnter = false;

	while (!isEnter) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();

			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::Enter) {
					isEnter = true;
					room.append(room[0]);
				}
			}

			if (event.type == sf::Event::MouseButtonPressed && !isEnter) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					sf::Vector2i cursorPos = sf::Mouse::getPosition(window);

					room.append(sf::Vector2f(cursorPos.x, cursorPos.y));
					room[ind].color = sf::Color::Black;
					++ind;
				}
			}
		}

		window.clear(sf::Color::White);

		window.draw(room);
		window.display();
	}

	for (long long i = 0; i < ind; ++i) gallery.add(point(read_x(room[i].position.x), read_y(room[i].position.y, window.getSize().y)));
}
void paper::draw_gallery() {
	for (long long i = 0; i < gallery.size; ++i) {
		room.append(sf::Vector2f(draw_x(gallery[i].x), draw_y(gallery[i].y, window.getSize().y)));
		room[i].color = sf::Color::Black;
	}
	room.append(room[0]);

	window.clear(sf::Color::White);

	window.draw(room);
	window.display();
}
team paper::read_team() {
	long long ind = 0;
	team t;
	bool isEnter = false;
	points.clear();

	while (!isEnter) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();

			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::Enter) isEnter = true;
			}

			if (event.type == sf::Event::MouseButtonPressed && !isEnter) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					sf::Vector2i cursorPos = sf::Mouse::getPosition(window);
					t.add(guard(read_x(cursorPos.x), read_y(cursorPos.y, window.getSize().y), 1));

					sf::CircleShape circle(3);
					circle.setFillColor(sf::Color::Blue);
					circle.setPosition(cursorPos.x, cursorPos.y);

					points.push_back(circle);
				}
			}
		}

		window.clear(sf::Color::White);

		window.draw(room);
		for (const auto &circle : points) window.draw(circle);
		window.display();
	}

	return t;
}
void paper::draw_team(team &t) {
	points.clear();
	for (long long i = 0; i < t.size; ++i) {
		sf::CircleShape circle(3);
		circle.setFillColor(sf::Color::Blue);
		circle.setPosition(draw_x(t[i].x), draw_y(t[i].y, window.getSize().y));

		points.push_back(circle);
	}

	window.clear(sf::Color::White);

	window.draw(room);
	for (const auto &circle : points) window.draw(circle);
	window.display();
}
void paper::draw_area(team &t) {
	for (const auto &i : t.polygons_area()) {
		sf::VertexArray convex(sf::LineStrip, (i.outer().size()));
		long long ind = 0;
		for(const auto &point : i.outer()) {
			convex[ind] = sf::Vector2f(draw_x(point.x()), draw_y(point.y(), window.getSize().y));
			convex[ind].color = sf::Color::Red;
			++ind;
		}
		polygons.push_back(convex);
	}

	while (window.isOpen()) {
    	sf::Event event;
    	while (window.pollEvent(event)) {
     		if (event.type == sf::Event::Closed) window.close();
      	}

      	window.clear(sf::Color::White);

		window.draw(room);
		for (const auto &circle : points) window.draw(circle);
		for (const auto &convex : polygons) window.draw(convex);
		window.display();
  }
}
