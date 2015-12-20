#include <sys/wait.h>
#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <memory>
#include <thread>
#include <cstdio>
#include <vector>


class ThreadLaunchProcessus
{
    public:
        ThreadLaunchProcessus(const std::string& nameProg, const std::vector<float>& input);

        void run();
        void stop();

        unsigned int numberFunctionRun() const;

    private:
        std::string nameProg;
        std::vector<float> input;

        int currentChild;
        std::shared_ptr<std::thread> thread;
        unsigned int numberFunctionLaunched;

        bool isRunning;

        void runThread();
        void writeToPipe(int fd);
};
