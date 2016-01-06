#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "point.h"

class Obstacle {
private:
	float x;
	float y;
	float halfWidth;
	float halfHeight;
	float angle;
public:
	Obstacle(float x, float y, float width, float heigth, float angle);
	float getX() const;
	float getY() const;
	float getWidth() const;
	float getHeight() const;
	void getCorners(Point out[]) const;
};

#endif
