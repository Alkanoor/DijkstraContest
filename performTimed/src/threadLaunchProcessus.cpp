#include "../include/threadLaunchProcessus.hpp"


ThreadLaunchProcessus::ThreadLaunchProcessus(const std::string& nameProg, const std::vector<float>& input) :
    currentChild(-1),
    numberFunctionLaunched(0)
{
    this->nameProg = nameProg;
    this->input = input;
}

void ThreadLaunchProcessus::run()
{
    isRunning = true;
    thread = std::shared_ptr<std::thread>(new std::thread(&ThreadLaunchProcessus::runThread,this));
}

void ThreadLaunchProcessus::stop()
{
    isRunning = false;
    kill(currentChild,SIGKILL);
    thread->join();
}

unsigned int ThreadLaunchProcessus::numberFunctionRun() const
{return numberFunctionLaunched;}

void ThreadLaunchProcessus::runThread()
{
    while(isRunning)
    {
        pid_t pid;
        int pipeParentToChild[2];
        int pipeChildToParent[2];

        if(pipe(pipeParentToChild))
        {
            std::cerr<<"Pipe failed"<<std::endl;
            exit(-1);
        }
        if(pipe(pipeChildToParent))
        {
            std::cerr<<"Pipe failed"<<std::endl;
            exit(-1);
        }

        pid = fork();
        if(pid<0)
        {
            std::cerr<<"Error during fork"<<std::endl;
            exit(-1);
        }
        else if(!pid)
        {
            isRunning = false;
            close(pipeChildToParent[0]);
            close(pipeParentToChild[1]);

            //write current pid to parent
            FILE *stream = fdopen(pipeChildToParent[1], "w");
            fprintf(stream,"%d",getpid());
            fclose(stream);

            //set current stdin from pipe for exec
            dup2(pipeParentToChild[0],0);
            close(pipeParentToChild[0]);

            close(1);

            char* args[] = {NULL};
            if(execv(nameProg.c_str(),args)<0)
            {
                std::cerr<<"Error exec : program "<<nameProg<<" doesn't exist"<<std::endl;
                exit(-1);
            }
        }
        else
        {
            close(pipeParentToChild[0]);
            close(pipeChildToParent[1]);

            //modify current child pid from what is sent from child
            FILE *stream = fdopen(pipeChildToParent[0], "r");
            if(fscanf(stream,"%d",&currentChild)<=0)
            {
                std::cerr<<"Error handling data with fscanf"<<std::endl;
                exit(-1);
            }
            fclose(stream);

            //send data to child program
            writeToPipe(pipeParentToChild[1]);

            int status;
            wait(&status);
            if((char)WEXITSTATUS(status)<0)
                exit(-1);
        }
        numberFunctionLaunched++;
    }
}

void ThreadLaunchProcessus::writeToPipe(int fd)
{
    FILE *stream = fdopen(fd, "w");
    for(unsigned int i=0;i<input.size();i++)
        fprintf(stream,"%f ",input[i]);
    fclose(stream);
}
