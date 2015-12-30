#include <stdio.h>
#include <stdlib.h>
#include "obstacles.h"
#include "point.h"
#include <vector>

using namespace std;

void path(float xStart, float yStart, float xStop, float yStop, int nbObstacles, vector<Obstacle> obstacles, int output = 0);

int main()  {
	int check;
	float xStart, yStart, xStop, yStop, trash,obstaclex, obstacley, obstacleHalfWidth, obstacleHalfHeight, obstacleAngle;
	check = scanf("%f", &trash);
	check = scanf("%f", &trash);
	check = scanf("%f", &trash);
	check = scanf("%f", &xStart);
	check = scanf("%f", &yStart);
	check = scanf("%f", &xStop);
	check = scanf("%f", &yStop);
	check = scanf("%f", &obstaclex);
	int nbObstacles = 0;
	vector<Obstacle> obstacles;
	while (check != 0) {
		check = scanf("%f", &obstacleHalfWidth);
		check = scanf("%f", &obstacley);
		check = scanf("%f", &obstacleHalfHeight);
		check = scanf("%f", &obstacleAngle);
		Obstacle obs(obstaclex, obstacley, obstacleHalfWidth, obstacleHalfHeight, obstacleAngle);
		obstacles.push_back(obs);
		nbObstacles++;
		check = scanf("%f", &obstaclex);
	}
	printf("%f %f ", xStart, yStart);
	path(xStart, yStart, xStop, yStop, nbObstacles, obstacles);
    return 0;
}

void path(float xStart, float yStart, float xStop, float yStop, int nbObstacles, vector<Obstacle> obstacles, int output) {
	for (int i = 0; i < nbObstacles; i++) {
		Obstacle o = obstacles[i];
		Point out[4] {Point(0,0), Point(0,0), Point(0,0), Point(0,0)};
		o.getCorners(out);
		//for (int j = 0; j < 4; j++)
		//{
			//Point c = out[j];
			Point c = out[0];
			if ((xStart < c.x && xStop > c.x) || (xStop < c.x && xStart > c.x)) {
				if ((yStart < c.y && yStop > c.y) || (yStop < c.x && yStart > c.y)) {
					path(xStart, yStart, c.x, c.y, nbObstacles, obstacles, 1);
					path(c.x, c.y, xStop, yStop, nbObstacles, obstacles, 1);
				}
			}
		//}
	}
	if (output) {
		printf("%f %f ", xStop, yStop);
	}
}
