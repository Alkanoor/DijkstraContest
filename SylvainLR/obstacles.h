#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "point.h"

class Obstacle {
private:
	int x;
	int y;
	int width;
	int height;
public:
	Obstacle(int x, int y, int width, int heigth);
	int getX() const;
	int getY() const;
	int getWidth() const;
	int getHeight() const;
	void getCorners(Point out[]) const;
};

#endif
