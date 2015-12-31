#include <stdio.h>
#include <stdlib.h>
#include "obstacles.h"
#include "point.h"
#include <vector>
#include "path.h"
#include <sstream>
#include <iostream>
using namespace std;

int main()  {
	int check;
	float xStart, yStart, xStop, yStop, tableWidth, tableHeight, radius, obstaclex, obstacley, obstacleHalfWidth, obstacleHalfHeight, obstacleAngle;
	check = scanf("%f", &tableWidth);
	check = scanf("%f", &tableHeight);
	check = scanf("%f", &radius);
	check = scanf("%f", &xStart);
	check = scanf("%f", &yStart);
	Point start(xStart, yStart);
	check = scanf("%f", &xStop);
	check = scanf("%f", &yStop);
	Point stop(xStop, yStop);
	int nbObstacles = 0;
	vector<Obstacle> obstacles;
	while (cin >> obstaclex) {
		check = scanf("%f", &obstacleHalfWidth);
		check = scanf("%f", &obstacley);
		check = scanf("%f", &obstacleHalfHeight);
		check = scanf("%f", &obstacleAngle);
		Obstacle obs(obstaclex, obstacley, obstacleHalfWidth, obstacleHalfHeight, obstacleAngle);
		obstacles.push_back(obs);
		nbObstacles++;
	}
	printf("%f %f ", xStart, yStart);
	stringstream ss;
	path(start, stop, nbObstacles, obstacles/*, ss*/);
	return 0;
}
