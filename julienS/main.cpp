#include <unistd.h>
#include <iostream>
#include <fstream>
#include <array>

#include "include/AStar.hpp"


int main(int argc, char* argv[])
{
    float tableWidth, tableHeight;
    float robotRadius;
    float startX, startY, endX, endY;

    std::cin>>tableWidth;
    std::cin>>tableHeight;
    std::cin>>robotRadius;
    std::cin>>startX;
    std::cin>>startY;
    std::cin>>endX;
    std::cin>>endY;

    float tmp;
    unsigned int counter=0;
    std::vector<Obstacle> obstacles;
    std::array<float,5> obstacleConstruction;
    while(std::cin>>tmp)
    {
        obstacleConstruction[counter%5] = tmp;
        counter++;
        if(!(counter%5))
            obstacles.push_back(Obstacle(obstacleConstruction[0],obstacleConstruction[1]+robotRadius,obstacleConstruction[2],obstacleConstruction[3]+robotRadius,obstacleConstruction[4]));
    }


    AStar toCompute(tableWidth,tableHeight,startX,startY,endX,endY);
    toCompute.update(obstacles);
    toCompute.browse();

    std::vector<std::pair<float,float> > path = toCompute.getPath();
    for(unsigned int i=0;i<path.size();i++)
        std::cout<<path[i].first<<" "<<path[i].second<<std::endl;

    return 0;
}
