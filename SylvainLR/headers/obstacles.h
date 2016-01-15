/*
*	This class is designed to represent an obstacle (unexpected, isn't it !!)
*	Obstacles are the elements on the table. They prevent the robot from navigating
*	through them.
*/


#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "point.h"

class Obstacle {
private:
	//The x coordinate of the center of the obstacle
	float x;
	//The y coordinate of the center of the obstacle 
	float y;
	//The half width of the obstacle (in the x direction)
	float halfWidth;
	//The half 'height' of the obstacle (in the y direction)
	float halfHeight;
	//The angle of the obstacle (in degrees) : it's anti-trigonometric and 0° is the y+ axis
	float angle;
public:
	//A simple constructor
	Obstacle(float x, float y, float width, float heigth, float angle);
	//No need for comment
	float getX() const;
	float getY() const;
	float getWidth() const;
	float getHeight() const;
	//Fill the array passed as parameter with the 4 corners (instances of the Point class) of the obstacle
	void getCorners(Point out[]) const;
};

#endif
