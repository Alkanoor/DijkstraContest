#include "utils.h"
#include <math.h>

int dcos (int angle) {
	return cos(angle * PI / 180);
}

int dsin (int angle) {
	return sin(angle * PI / 180);
}

int max(int a, int b) {
	if (a < b)
		return b;
	return a;
}

int min(int a, int b) {
	if (a < b)
		return a;
	return b;
}

int signof(int x) {
	if(x >= 0)
		return 1;
	return -1;
}

int determinant(Point p, Point p1, Point p2) {
	return (p.x - p1.x)*(p2.y - p1.y) - (p.y - p1.y) * (p2.x - p1.x);
}
