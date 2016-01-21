#include "../include/AStar.hpp"


AStar::AStar(unsigned int w, unsigned h, float xBeg, float yBeg, float xEnd, float yEnd)
{
    resize(w,h);
    update(std::pair<float,float>(xBeg,yBeg),std::pair<float,float>(xEnd,yEnd));
}

void AStar::resize(unsigned int w, unsigned h)
{
    land.resize(h);
    isNearCorner.resize(h);
    currentWeights.resize(h);
    currentParents.resize(h);
    for(unsigned int i=0;i<h;i++)
    {
        land[i].resize(w);
        isNearCorner[i].resize(w);
        currentWeights[i].resize(w);
        currentParents[i].resize(w);
    }

    for(unsigned int i=0;i<currentWeights.size();i++)
        for(unsigned int j=0;j<currentWeights[i].size();j++)
        {
            land[i][j] = true;
            isNearCorner[i][j] = 0;
            currentWeights[i][j] = -1;
            currentParents[i][j] = std::pair<int,int>(-1,-1);
        }
}

void AStar::update(const std::vector<Obstacle>& obstacles)
{
    for(unsigned int i=0;i<land.size();i++)
        for(unsigned int j=0;j<land[i].size();j++)
            land[i][j] = true;

    for(unsigned int i=0;i<obstacles.size();i++)
    {
        Rect tmp = obstacles[i].getBoundingBox();
        for(int k=(int)tmp.x;k<=(int)(tmp.x+tmp.w);k++)
            for(int l=(int)tmp.y;l<=(int)(tmp.y+tmp.h);l++)
                if(obstacles[i].isInObstacle(k,l)&&k>=0&&l>=0&&l<(int)land.size()&&k<(int)land[l].size())
                    land[l][k] = false;
    }

    int radius = 14;
    for(unsigned int i=0;i<obstacles.size();i++)
    {
        Vec v = obstacles[i].getCorner1();
        for(int o=v.y-radius;o<=v.y+radius;o++)
            for(int p=v.x-radius;p<=v.x+radius;p++)
                if(o>=0&&p>=0&&o<(int)isNearCorner.size()&&p<(int)isNearCorner[o].size())
                    isNearCorner[o][p] = (i+1)*4;
        v = obstacles[i].getCorner2();
        for(int o=v.y-radius;o<=v.y+radius;o++)
            for(int p=v.x-radius;p<=v.x+radius;p++)
                if(o>=0&&p>=0&&o<(int)isNearCorner.size()&&p<(int)isNearCorner[o].size())
                    isNearCorner[o][p] = (i+1)*4+1;
        v = obstacles[i].getCorner3();
        for(int o=v.y-radius;o<=v.y+radius;o++)
            for(int p=v.x-radius;p<=v.x+radius;p++)
                if(o>=0&&p>=0&&o<(int)isNearCorner.size()&&p<(int)isNearCorner[o].size())
                    isNearCorner[o][p] = (i+1)*4+2;
        v = obstacles[i].getCorner4();
        for(int o=v.y-radius;o<=v.y+radius;o++)
            for(int p=v.x-radius;p<=v.x+radius;p++)
                if(o>=0&&p>=0&&o<(int)isNearCorner.size()&&p<(int)isNearCorner[o].size())
                    isNearCorner[o][p] = (i+1)*4+3;
    }

    this->obstacles = obstacles;
}

void AStar::update(std::pair<float,float> initialPos, std::pair<float,float> finalPos)
{
    this->initialPos = initialPos;
    this->finalPos = finalPos;
}

void AStar::update(const std::vector<Obstacle>& obstacles, std::pair<float,float> initialPos, std::pair<float,float> finalPos)
{
    update(obstacles);
    update(initialPos, finalPos);
}

void AStar::browse()
{
    currentBestDistance = -1;

    if(initialPos.first<0||initialPos.second<0||initialPos.second>=land.size()||initialPos.first>=land[initialPos.second].size())
        if(!land[(int)initialPos.second][(int)initialPos.first])
            return;

    CustomTuple::resetTarget(finalPos.first,finalPos.second);

    bestGoalReached.first = (int)initialPos.first;
    bestGoalReached.second = (int)initialPos.second;

    std::priority_queue<CustomTuple> empty;
    std::swap(currentQueue, empty);

    currentQueue.push(CustomTuple((int)initialPos.first,(int)initialPos.second,0));
    currentWeights[(int)initialPos.second][(int)initialPos.first] = 0;

    bool hasBeenReached = false;
    int maxWeight = -1;
    while(!currentQueue.empty())
    {
        CustomTuple curElement = currentQueue.top();
        currentQueue.pop();
        if(curElement.posX==(int)finalPos.first&&curElement.posY==(int)finalPos.second)
        {
            hasBeenReached = true;
            maxWeight = curElement.weight;
        }
        for(unsigned int i=0;i<4;i++)
        {
            CustomTuple nextElement = curElement.nextElement(i);
            if(nextElement.posX>=0&&nextElement.posY>=0&&nextElement.posY<(int)land.size()&&nextElement.posX<(int)land[nextElement.posY].size())
                if(land[nextElement.posY][nextElement.posX])
                    if(currentWeights[nextElement.posY][nextElement.posX]<0||nextElement.weight<currentWeights[nextElement.posY][nextElement.posX])
                    {
                        currentWeights[nextElement.posY][nextElement.posX] = nextElement.weight;
                        currentParents[nextElement.posY][nextElement.posX] = std::pair<int,int>(curElement.posX,curElement.posY);
                        if(!hasBeenReached||(hasBeenReached&&nextElement.weight<maxWeight))
                            currentQueue.push(CustomTuple(nextElement.posX,nextElement.posY,nextElement.weight));
                        if(currentBestDistance<0||nextElement.distanceFromGoal<currentBestDistance)
                        {
                            currentBestDistance = nextElement.distanceFromGoal;
                            bestGoalReached.first = nextElement.posX;
                            bestGoalReached.second = nextElement.posY;
                        }
                    }
        }
    }

    constructPath();
}

const std::vector<std::pair<float,float> >& AStar::getPath()
{return currentPath;}

void AStar::constructPath()
{
    currentPath.clear();
    if(currentBestDistance<0)
        return;

    std::pair<int,int> curElement = bestGoalReached, nextElement;
    currentPath.push_back(finalPos);
    unsigned int i=0;

    int last = -1;
    while(curElement.first>=0&&curElement.second>=0&&currentWeights[curElement.second][curElement.first]>0)
    {
        curElement = currentParents[curElement.second][curElement.first];
        if(curElement.first>=0&&curElement.second>=0&&curElement.second<(int)isNearCorner.size()&&curElement.first<(int)isNearCorner[curElement.second].size()&&isNearCorner[curElement.second][curElement.first]>0)
        {
            if(last!=(int)isNearCorner[curElement.second][curElement.first])
            {
                Vec v;
                if(!(isNearCorner[curElement.second][curElement.first]%4))
                    v = obstacles[(int)(isNearCorner[curElement.second][curElement.first]/4)-1].getCorner1();
                else if((isNearCorner[curElement.second][curElement.first]%4)==1)
                    v = obstacles[(int)(isNearCorner[curElement.second][curElement.first]/4)-1].getCorner2();
                else if((isNearCorner[curElement.second][curElement.first]%4)==2)
                    v = obstacles[(int)(isNearCorner[curElement.second][curElement.first]/4)-1].getCorner3();
                else
                    v = obstacles[(int)(isNearCorner[curElement.second][curElement.first]/4)-1].getCorner4();
                currentPath.push_back(std::pair<float,float>(v.x,v.y));
                last = isNearCorner[curElement.second][curElement.first];
                i++;
            }
        }
    }
    currentPath.push_back(initialPos);

    //std::reverse(currentPath.begin(),currentPath.end());
}
