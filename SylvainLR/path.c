#include <stdio.h>
#include <vector>
#include "path.h"
#include <math.h>
#include <sstream>
#include <ostream>

using namespace std;

void path(Point start, Point stop, int nbObstacles, vector<Obstacle> obstacles, stringstream ss, int output) {
	for (int i = 0; i < nbObstacles; i++) {
		Obstacle o = obstacles[i];
		Point out[4] {Point(0,0), Point(0,0), Point(0,0), Point(0,0)};
		o.getCorners(out);
		for (int j = 0; j < 4; j++)
		{
			Point c = out[j];
			if ((start.x < c.x && stop.x > c.x) || (stop.x < c.x && start.x > c.x)) {
				if ((start.y < c.y && stop.y > c.y) || (stop.y < c.x && start.y > c.y)) {
					path(start, c, nbObstacles, obstacles, 1);
					path(c, stop, nbObstacles, obstacles, 1);
				}
			}
		}
	}
	if (output) {
		printf("%f %f ", stop.x, stop.y);
	}
}

float distance (float xStart, float yStart, float xStop, float yStop) {
	float deltaX = xStop - xStart;
	float deltaY = yStop - yStart;
	return sqrt(deltaX * deltaX + deltaY * deltaY);
}

float distance(Point start, Point stop) {
	float deltaX = stop.x - start.x;
	float deltaY = stop.y - start.y;
	return sqrt(deltaX * deltaX + deltaY *deltaY);
}

void print(ostream &s, char* text) {
	s << text;
}
