#include <cmath>
#include <cstdio>
#include <unistd.h>

#include <AGP/components/ui/view.h>
#include <AGP/components/interface/team.h>
#include <AGP/components/interface/genetic_algorithm.h>

int main() {
	freopen("input.txt", "r", stdin);
	view w;
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
