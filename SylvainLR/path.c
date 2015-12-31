#include <stdio.h>
#include <vector>
#include "path.h"
#include <math.h>
#include <sstream>
#include <ostream>

using namespace std;

void path(Point start, Point stop, int nbObstacles, vector<Obstacle> obstacles,/* stringstream ss,*/ int output) {
	Point out[4] = {Point(0,0), Point(0,0), Point(0,0), Point(0,0)};
	for (int i = 0; i < nbObstacles; i++) {
		if (intersect(start, stop, obstacles[i]) == 1) {
			obstacles[i].getCorners(out);
			//a améliorer
			int j = 0;
			if (start.x == out[j].x && start.y == out[j].y) {
				j++;
			}
			path(start, out[j], nbObstacles, obstacles);
			path(out[j], stop, nbObstacles, obstacles);
			return;
		}
	}
	//En l'absence d'obstacles sur la route
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

/*
*return 0 : pas d'intersection
*return 1 : intersection
*return 2 : erreur
*/

int intersect(Point start, Point stop, Obstacle o) {
	Point out[4] = {Point(0,0), Point(0,0), Point(0,0), Point(0,0)};
	o.getCorners(out);
	//Droite start-stop : a1 X + b1 = Y
	if (start.x != stop.x) {
		float a1 = (start.y - stop.y) / (start.x - stop.x);
		float b1 = start.y - a1 * start.x;
		for (int i = 0; i < 4; i++) {
		    Point c1 = out[i%4];
		    Point c2 = out[(i+1)%4];
		    if (c1.x != c2.x) {
			    float a2 = (c1.y - c2.y) / (c1.x - c2.x);
			    if (a1 == a2) {
				    return 0;
			    } else {
				    float b2 = c1.y - a2 * c1.x;
				    float x = (b2 - b1) / (a1 - a2);
				    if ((start.x < x && stop.x > x) || (start.x > x && stop.x < x)) {
					    return 1;
				    } else {
					    return 0;
				    }
			    }
		    } else {
			    float y = a1 * c1.x + b1;
			    if ((c1.y < y && c2.y > y) || (c1.y > y && c2.y < y)) {
				    return 1;
			    } else {
				    return 0;
			    }
		    }
		}
	} else {
		for (int i = 0; i < 4; i++) {
			Point c1 = out[i%4];
			Point c2 = out[(i+1)%4];
			if ((c1.x < start.x && c2.x > start.x) || (c1.x > start.x && c2.x < start.x)) {
				if (c1.x != c2.x) {
					float a2 = (c1.y - c2.y) / (c1.x - c2.x);
					float b2 = c1.y - a2 * c1.x;
					float y = a2 * start.x + b2;
					if ((start.y < y && stop.y > y) || (start.y > y && stop.y < y)) {
						return 1;
					} else {
						return 0;
					}
				}
			}
		}
	}
	return 2;
}

