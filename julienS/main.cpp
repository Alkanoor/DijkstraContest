#include <unistd.h>
#include <iostream>
#include <fstream>


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

    std::cout<<startX<<" "<<startY<<" "<<200<<" "<<50<<" "<<295<<" "<<280<<" "<<endX<<" "<<endY<<std::endl;

    /*float tmp;
    while(std::cin>>tmp)
        std::cout<<tmp<<std::endl;*/

    return 0;
}
