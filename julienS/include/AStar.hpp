#ifndef ASTAR_HPP
#define ASTAR_HPP


#include <algorithm>
#include <vector>
#include <queue>

#include "CustomTuple.hpp"
#include "Obstacle.hpp"


class AStar
{
    public:
        AStar(unsigned int w, unsigned h, float xBeg, float yBeg, float xEnd, float yEnd);

        void resize(unsigned int w, unsigned h);
        void update(const std::vector<Obstacle>& obstacles);
        void update(std::pair<float,float> initialPos, std::pair<float,float> finalPos);
        void update(const std::vector<Obstacle>& obstacles, std::pair<float,float> initialPos, std::pair<float,float> finalPos);

        void browse();
        const std::vector<std::pair<float,float> >& getPath();

        static std::pair<float,float> proj(float x, float y, float x1, float y1, float x2, float y2);

    private:
        std::pair<float,float> initialPos;
        std::pair<float,float> finalPos;

        std::vector<Obstacle> obstacles;
        std::vector<std::vector<bool> > land;
        std::vector<std::vector<int> > currentWeights;
        std::vector<std::vector<unsigned int> > isNearCorner;
        std::vector<std::vector<std::pair<int,int> > > currentParents;
        std::priority_queue<CustomTuple> currentQueue;

        std::pair<int,int> bestGoalReached;
        int currentBestDistance;

        std::vector<std::pair<float,float> > currentPath;
        void constructPath();
        void clearPath(unsigned int i=0);
};


#endif
