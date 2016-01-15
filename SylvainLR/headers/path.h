/*
*	The core element of this small project.
*	Here, you can find the main functions to call in order to have a (potentially) useful result
*	
*	How does it work?? Let me try to explain it:
*	At the beginning, I draw a virtual line between the start point and the stop one.
*	Then, I deform this line in order to avoid the obstacles and provide a safe path for our robot
*	to reach the end of his dangerous journey.
*
*	This algorithm offers no guarantee about the optimality of the path(i.e. a shorter path can exist)
*	but in most common cases, it should return a rather good one.
*
*	Indeed, it was not designed to find the best path (A* or Dijkstra already exist and are very efficient)
*	but to provide a leight and quick solution. First test have revealed that it can be up to 10 times quicker
*	than an A*). Even if this figure is a bit higher than the truth, it proves that it is actually quicker than A*.
*
*	If you find cases where the path proposed is wrong, report it at
*	team@telecom-robotics.org or sylvain.leroux@telecom-paristech.fr
*
*/

#ifndef PATH_H
#define PATH_H

#include "obstacles.h"
#include <vector>
#include <ostream>
#include <sstream>

//The main function, the one that you really need
void path(Point start, Point stop, int nbObstacles, std::vector<Obstacle> obstacles,/* std::stringstream ss,*/ int output = 1);
//Give the euclidian distance between two points
float distance(float xStart, float yStart, float xStop, float yStop);
float distance(Point start, Point stop);
//Print the string (char*) passed as parameter in the stream passed as parameter
void print(std::ostream, char*);
//Tells if a straight line between start and stop intersects the obstacle o
int intersect(Point start, Point stop, Obstacle o);

#endif
