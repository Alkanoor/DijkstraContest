#include <stdio.h>
#include <vector>
#include "path.h"
#include <math.h>
#include <sstream>
#include <ostream>
#include <unistd.h>

using namespace std;

extern float xMax, yMax;

void path(Point start, Point stop, int nbObstacles, vector<Obstacle> obstacles,/* stringstream ss,*/ int output) {
	Point out[4] = {Point(0,0), Point(0,0), Point(0,0), Point(0,0)};
	/*printf("start ");
	start.print();
	printf("stop ");
	stop.print();*/
	for (int i = 0; i < nbObstacles; i++) {
		if (intersect(start, stop, obstacles[i]) == 1) {
			obstacles[i].getCorners(out);
			//a améliorer
			int j = 0;
			if (start.x < obstacles[i].getX()) {
				if (start.y < obstacles[i].getY()) {
					//Bottom left corner
					j = 3;
				} else {
					//Bottom right corner
					j = 2;
				}
			} else {
				if (start.y < obstacles[i].getY()) {
					//Top left corner
					j = 0;
				} else {
					//Top right corner
					j = 1;
				}
			}
			int k = 0;
			while ((start.x == out[j].x && start.y == out[j].y) || (stop.x == out[j].x && stop.y == out[j].y) || (out[j].x < 0 || out[j].x > xMax || out[j].y < 0 || out[j].y > yMax)) {
				j++;
				j = j%4;
				k++;
				if (k > 3) {
					return;
				}
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
			//printf("i = %i\n", i);
		    if (c1.x != c2.x) {
				/*printf("c1 ");
				c1.print();
				printf("c2 ");
				c2.print();*/
			    float a2 = (c1.y - c2.y) / (c1.x - c2.x);
			    if (a1 != a2) {
				    float b2 = c1.y - a2 * c1.x;
				    float x = (b2 - b1) / (a1 - a2);
					//printf("x = %f\n", x);
					/*printf("start ");
					start.print();
					printf("stop ");
					stop.print();
					printf("2.02 * x = %f 0.98 * x = %f\n", 1.02 * x, 0.98 * x);*/
				    if ((start.x < 0.98 * x && stop.x > 1.02 * x) || (start.x > 1.02 * x && stop.x < 0.98 * x)) {
					    //printf("return\n");
						return 1;
				    }
			 	}
		    } else {
				if ((start.x < c1.x && stop.x > c1.x) || (start.x > c1.x && stop.x < c1.x)) {
			    	float y = a1 * c1.x + b1;
					//printf("y = %f c1.y = %f c2.y = %f\n", y, c1.y, c2.y);
			    	if ((c1.y < 0.98 * y && c2.y > 1.02 * y) || (c1.y > 1.02 * y && c2.y < 0.98 * y)) {
				   		return 1;
			    	}
				}
		    }
		}
		return 0;
	} else {
		//printf("else");
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
					}
				}
			}
		}
		return 0;
	}
	//printf("error");
	return 2;
}

