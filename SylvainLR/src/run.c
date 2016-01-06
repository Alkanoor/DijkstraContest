#include <stdio.h>
#include <stdlib.h>
#include "obstacles.h"
#include "point.h"
#include <vector>
#include "path.h"
#include <iostream>
#include "run.h"

using namespace std;

float xMax, yMax, radius;

void printPoint(float x, float y, ostream &s) {
	s << x << " " << y << " ";
}

int run()  {
	int check;
	float xStart, yStart, xStop, yStop, obstaclex, obstacley, obstacleHalfWidth, obstacleHalfHeight, obstacleAngle;
	check = scanf("%f", &xMax);
	check = scanf("%f", &yMax);
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
	/*Point out[4] = {Point(0,0), Point(0,0), Point(0,0), Point(0,0)};
	obstacles[0].getCorners(out);
	printf("top left : ");
	out[0].print();
	printf("top right : ");
	out[1].print();
	printf("bottom right : ");
	out[2].print();
	printf("bottom left : ");
	out[3].print();
	*/
	printPoint(xStart, yStart);
	path(start, stop, nbObstacles, obstacles/*, ss*/);
	return 0;
}
