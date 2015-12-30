#include <stdio.h>
#include <stdlib.h>
#include "obstacles.h"
#include "point.h"

void path(float xStart, float yStart, float xStop, float yStop, int nbObstacles, Obstacle obstacles[]);

int main()  {
	int check;
	float xStart, yStart, xStop, yStop, trash,obstacle1x, obstacle1y, obstacle1HalfWidth, obstacle1HalfHeight, obstacle1Angle;
	check = scanf("%f", &trash);
	check += scanf("%f", &trash);
	check += scanf("%f", &trash);
	check += scanf("%f", &xStart);
	check += scanf("%f", &yStart);
	check += scanf("%f", &xStop);
	check += scanf("%f", &yStop);
	check += scanf("%f", &obstacle1x);
	check += scanf("%f", &obstacle1HalfWidth);
	check += scanf("%f", &obstacle1y);
	check += scanf("%f", &obstacle1HalfHeight);
	check += scanf("%f", &obstacle1Angle);
	if (check != 12) {
		return 1;
	}
	int nbObstacles = 1;
	printf("%f %f 7.0 7.0", xStart, yStart);
	Obstacle obs(obstacle1x, obstacle1y, obstacle1HalfWidth, obstacle1HalfHeight, obstacle1Angle);
	Obstacle obstacles[1] = {obs};
	path(xStart, yStart, xStop, yStop, nbObstacles, obstacles);
    return 0;
}

void path(float xStart, float yStart, float xStop, float yStop, int nbObstacles, Obstacle obstacles[]) {
	for (int i = 0; i < nbObstacles; i++) {
		Obstacle o = obstacles[i];
		Point out[4] {Point(0,0), Point(0,0), Point(0,0), Point(0,0)};
		o.getCorners(out);
		for (int j = 0; j < 4; j++)
		{
			Point c = out[j];
			if ((xStart < c.x && xStop > c.x) || (xStop < c.x && xStart > c.x)) {
				if ((yStart < c.y && yStop > c.y) || (yStop < c.x && yStart > c.y)) {
					path(xStart, yStart, c.x, c.y, nbObstacles, obstacles);
					path(c.x, c.y, xStop, yStop, nbObstacles, obstacles);
				}
			}
		}
	}
	printf("%f %f ", xStop, yStop);
}
