#include <iostream>
#include <sstream>
#include <vector>
#include <string>

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

    std::cout<<"Points : "<<std::endl;
    for(unsigned int i=0;i<points.size();i++)
        std::cout<<points[i]<<" ";
    std::cout<<std::endl<<"Situation : "<<std::endl;
    for(unsigned int i=0;i<situation.size();i++)
        std::cout<<situation[i]<<" ";
    std::cout<<std::endl;

    return 0;
}
