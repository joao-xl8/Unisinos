#include <unistd.h>
#include <stdio.h>

int main(int argc, char *arcv[])
{
    pid_t id = fork(); // create a copy of the process and execute from this point. COPY ALL MEMORY

    if (id != 0) // child process get 0
    {
        printf("Im the parent process %d, my parent is: %d\n", getpid(), getppid());
    } else {
       printf("Im the child process %d, my parent is: %d\n", getpid(), getppid());
    }
    
    printf("Hello World\n");
    return 0;
}