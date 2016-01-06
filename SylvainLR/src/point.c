#include "point.h"
#include <iostream>

Point::Point(float x, float y) {
	this->x = x;
	this->y = y;
}

void Point::print(std::ostream &s) {
	s << this->x << " " << this->y << " ";
}
