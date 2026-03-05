#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

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
        while (1)
        {
            printf("Loop text\n");
            usleep(500000);
        }
    }
    else
    {
        sleep(1);
        kill(pid, SIGKILL);
        wait(nullptr);
        printf("Im the parent process %d, my parent is: %d\n", getpid(), getppid());
    }
    
    return 0;
}