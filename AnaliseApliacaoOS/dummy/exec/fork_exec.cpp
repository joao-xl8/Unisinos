#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char *arcv[])
{
    pid_t id = fork();
    int n;

    if (id == 0)
    {
        execlp("ls", "ls","-la", NULL);
        // CODE BELOW NOT EXECUTED
    }
    else
    {   
        wait(nullptr);
        printf("Im the parent process %d, my parent is: %d\n", getpid(), getppid());
    }
 
    return 0;
}