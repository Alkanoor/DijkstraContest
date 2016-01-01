#include "point.h"
#include <stdio.h>

Point::Point(float x, float y) {
	this->x = x;
	this->y = y;
}

void Point::print() {
	printf("x = %f, y = %f\n", this->x, this->y);
}
