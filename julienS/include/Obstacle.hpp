#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP


#include <cmath>

#ifndef PI
#define PI 3.14156265
#endif


class Vec
{
    public:
        Vec(float x=0, float y=0);
        float x, y;
};

class Rect
{
    public:
        Rect(float x=0, float y=0, float w=0, float h=0);
        float x, y, w, h;
};

class Obstacle
{
    public:
        Obstacle(float xPosCenter, float halfWidth, float yPosCenter, float halfHeight, float rotation);

        Vec getCorner1() const;
        Vec getCorner2() const;
        Vec getCorner3() const;
        Vec getCorner4() const;

        bool isInObstacle(float x, float y) const;
        const Rect& getBoundingBox() const;

    private:
        float xPosCenter, halfWidth, yPosCenter, halfHeight, rotation;
        bool orientation;
        Rect boundingBox;
        Vec tanVec[2];
        Vec point[2];
        Vec pointBis[2];
};


#endif
