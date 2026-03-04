#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char *arcv[])
{
    pid_t id = fork();
    int n;

    if (id == 0)
    {
        n = 1;
        printf("Im the child process %d, my parent is: %d\n", getpid(), getppid());
        sleep(1);
    }
    else
    {
        n = 6;
        printf("Im the parent process %d, my parent is: %d\n", getpid(), getppid());
    }
    int res = wait(nullptr); // without wait() it will print 6 1 7 2 8 3 9 4 10 5

    for (int i = n; i < n + 5; i++)
    {
        printf("%d\n", i);
        fflush(stdout); // use to insta flush (print) the printf value and not use efficient calls
    }

    if (res == -1)
    {
        printf("No process to wait for\n");
    }
    else
    {
        printf("%d finished\n", res);
    }

    return 0;
}