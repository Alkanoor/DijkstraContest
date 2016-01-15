/*
*	A simple class to represent a point, i.e. a couple of two coordinates
*/

#ifndef POINT_H
#define POINT_H

#include <iostream>

class Point {
private:
public:
 float x, y;
 Point (float x, float y);
 //Print the coordinates of the point on the stream passed as parameter
 //Format is : "x y" (obvious, don't you think??)
 void print(std::ostream &s = std::cout);
};

#endif
