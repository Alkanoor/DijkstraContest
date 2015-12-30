#include "../include/Obstacle.hpp"


Vec::Vec(float x, float y)
{
    this->x = x;
    this->y = y;
}

Rect::Rect(float x, float y, float w, float h)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

Obstacle::Obstacle(float xPosCenter, float halfWidth, float yPosCenter, float halfHeight, float rotation)
{
    this->xPosCenter = xPosCenter;
    this->halfWidth = halfWidth;
    this->yPosCenter = yPosCenter;
    this->halfHeight = halfHeight;
    this->rotation = rotation;

    float angle = -rotation/180.f*PI;

    float w = 2*(fabs(halfWidth*cos(angle))+fabs(halfHeight*sin(angle)));
    float h = 2*(fabs(halfHeight*cos(angle))+fabs(halfWidth*sin(angle)));
    boundingBox = Rect(xPosCenter-w/2,yPosCenter-h/2,w,h);

    tanVec[0] = Vec(sin(angle),cos(angle));
    tanVec[1] = Vec(-cos(angle),sin(angle));
    point[0] = Vec(xPosCenter-halfWidth*cos(angle)+halfHeight*sin(angle),yPosCenter+halfWidth*sin(angle)+halfHeight*cos(angle));
    point[1] = Vec(2*xPosCenter-point[0].x,2*yPosCenter-point[0].y);
}

bool Obstacle::isInObstacle(float x, float y) const
{
    if(x<boundingBox.x||y<boundingBox.y||x>=boundingBox.x+boundingBox.w||y>=boundingBox.y+boundingBox.h)
        return false;

    for(unsigned int i=0;i<2;i++)
        if((x-point[0].x)*tanVec[i].x+(y-point[0].y)*tanVec[i].y>0)
            return false;

    for(unsigned int i=0;i<2;i++)
        if((x-point[1].x)*(-tanVec[i].x)+(y-point[1].y)*(-tanVec[i].y)>0)
            return false;

    return true;
}

const Rect& Obstacle::getBoundingBox() const
{return boundingBox;}
