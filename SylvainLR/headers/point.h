#ifndef POINT_H
#define POINT_H

#include <iostream>

class Point {
private:
public:
 float x, y;
 Point (float x, float y);
 void print(std::ostream &s = std::cout);
};

#endif
