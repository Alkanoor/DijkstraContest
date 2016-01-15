#include <stdio.h>
#include <stdlib.h>
#include "obstacles.h"
#include "point.h"
#include <vector>
#include "path.h"
#include "run.h"

using namespace std;

float xMax, yMax, radius;

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
	vector<Point> points = {};
	start.print();
	points.push_back(start);
	path(start, stop, nbObstacles, obstacles, &points);
	for (auto i : points) {
		i.print(cout);
	}
	int size = points.size();
	Point path[size];
	for (int i = 0; i < size; i++) {
		path[i] = points.at(i);
	}
	return 0;
}
