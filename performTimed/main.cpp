#include <chrono>

#include "include/threadLaunchProcessus.hpp"


int main(int argc, char* argv[])
{
    if(argc<2)
    {
        std::cout<<"Not enough arguments were supplied to program, please usage with your program path as argument"<<std::endl;
        return 0;
    }

    std::vector<float> input;
    float tmp;
    while(std::cin>>tmp)
        input.push_back(tmp);

    if(input.size()<8)
    {
        std::cout<<"There isn't enough information in input, please check the format"<<std::endl;
        return 0;
    }

    float delay = 10;
    if(argc>3)
    {
        std::string arg3(argv[3]);
        delay = std::stof(arg3);
    }

    std::string nameProg(argv[1]);
    ThreadLaunchProcessus t(nameProg,input);
    t.run();

    typedef std::chrono::high_resolution_clock Clock;
    typedef std::chrono::milliseconds milliseconds;
    Clock::time_point start = Clock::now();

    while(std::chrono::duration_cast<milliseconds>(Clock::now()-start).count()<delay*1000)
        usleep(50000);

    t.stop();
    std::cout<<t.numberFunctionRun()<<" functions were run for program "<<nameProg;
    if(argc>2)
        std::cout<<" and situation "<<argv[2];
    std::cout<<" during a delay of "<<delay<<" seconds"<<std::endl;

    return 0;
}
