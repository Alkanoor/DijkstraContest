#ifndef CUSTOMTUPLE_HPP
#define CUSTOMTUPLE_HPP


#define NUMBER_POINTS_SAFE 10

#include <cmath>


class CustomTuple
{
    public:
        CustomTuple(int a, int b, int c);
        bool operator < (const CustomTuple& other) const;
        CustomTuple nextElement(int i) const;

        static void resetTarget(int x, int y);

        int posX, posY;
        int weight, distanceFromGoal;

    private:
        static int posGoalX, posGoalY;
};


#endif
