#ifndef PATH_H
#define PATH_H

#include "obstacles.h"
#include <vector>
#include <ostream>
#include <sstream>

void path(Point start, Point stop, int nbObstacles, std::vector<Obstacle> obstacles,/* std::stringstream ss,*/ int output = 1);
float distance(float xStart, float yStart, float xStop, float yStop);
float distance(Point start, Point stop);
void print(std::ostream, char*);
int intersect(Point start, Point stop, Obstacle o);

#endif
