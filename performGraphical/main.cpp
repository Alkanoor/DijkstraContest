#include <iostream>
#include <sstream>
#include <vector>
#include <string>

#include "include/customWindow.hpp"


int main()
{
    std::string firstString, secondString;
    std::vector<float> points, situation;

    std::string t;
    while(std::cin>>t&&t!="%")
        firstString += t+" ";
    while(std::cin>>t&&t!="%")
        secondString += t+" ";

    std::istringstream iss1(firstString);
    std::istringstream iss2(secondString);
    float f;
    while(iss1>>f)
        points.push_back(f);
    while(iss2>>f)
        situation.push_back(f);

    if(situation.size()<7)
    {
        std::cerr<<"There is not enough parameters for simulation, if this was run with makefile please check everything that can be checked, that's not normal"<<std::endl;
        exit(-1);
    }

    CustomWindow window(900,600,"Graphical result");
    window.setEnvironment(situation);
    window.setTrajectory(points);
    window.runUntilQuit();

    return 0;
}
