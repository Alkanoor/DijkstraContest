#include <unistd.h>
#include <iostream>
#include <fstream>


int main(int argc, char* argv[])
{
    std::ofstream log("log.txt",std::ios::out|std::ios::app);

    log<<argc<<std::endl;
    for(int i=0;i<argc;i++)
        log<<argv[i]<<std::endl;

    log<<"==============="<<std::endl;
    float tmp;
    while(std::cin>>tmp)
        log<<tmp<<std::endl;

    usleep(200000);

    return 0;
}
