#ifndef CUSTOMTUPLE_HPP
#define CUSTOMTUPLE_HPP


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
