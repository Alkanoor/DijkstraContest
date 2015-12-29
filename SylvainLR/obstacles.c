#include "obstacles.h"
#include "point.h"

Obstacle::Obstacle(int x, int y, int width, int height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

int Obstacle::getX() const{
	return this->x;
}

int Obstacle::getY() const{
	return this->y;
}

int Obstacle::getWidth() const{
	return this->width;
}

int Obstacle::getHeight() const{
	return this->height;
}

void Obstacle::getCorners(Point out[]) const{
	//Top Left Corner
	out[0].x = this->x - this->width/2;
	out[0].y = this->y + this->height/2;
	//Top Right Corner
	out[1].x = this->x + this->width/2;
	out[1].y = this->y + this->height/2;
	//Bottom Left Corner
	out[2].x = this->x - this->width/2;
	out[2].y = this->y - this->height/2;
	//Bottom Right Corner
	out[3].x = this->x + this->width/2;
	out[3].y = this->y - this->height/2;
}
