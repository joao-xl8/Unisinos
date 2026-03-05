#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <iostream>
#include <signal.h>

void handle_sigusr1(int sig) {
    std::cout << "(HINT) Multiplication is repetitive addition!" << std::endl;
}

int main(int argc, char *arcv[])
{
    pid_t pid = fork();
    int n;
    if (pid == -1)
    {
        return 1;
    }
    

    if (pid == 0)
    {
        sleep(5);
        kill(getppid(), SIGUSR1);
    }
    else
    {
        struct sigaction sa = { 0 };
        sa.sa_flags = SA_RESTART;
        sa.sa_handler = &handle_sigusr1;
        sigaction(SIGUSR1, &sa, nullptr);

        int x;
        std::cout << "What is the result of 3 x 5: ";
        std::cin >> x;
        std::cout << std::endl;

        if (x == 15)
        {
            std::cout << "Right!" << std::endl;
        } else
        {
            std::cout << "Wrong!" << std::endl;
        }       
        wait(nullptr);
    }
    
    return 0;
}