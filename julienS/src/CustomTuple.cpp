#include "../include/CustomTuple.hpp"


int CustomTuple::posGoalX = 0, CustomTuple::posGoalY = 0;


CustomTuple::CustomTuple(int a, int b, int c) :
    posX(a), posY(b), weight(c)
{
    distanceFromGoal = std::abs(posX-posGoalX)+std::abs(posY-posGoalY);
}

bool CustomTuple::operator < (const CustomTuple& other) const
{return distanceFromGoal+weight>other.distanceFromGoal+other.weight;}

CustomTuple CustomTuple::nextElement(int i) const
{
    if(!(i%4))
        return CustomTuple(posX+1,posY,weight+1);
    if((i%4)==1)
        return CustomTuple(posX-1,posY,weight+1);
    else if((i%4)==2)
        return CustomTuple(posX,posY+1,weight+1);
    else
        return CustomTuple(posX,posY-1,weight+1);
}

void CustomTuple::resetTarget(int x, int y)
{
    posGoalX = x;
    posGoalY = y;
}
