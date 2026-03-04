#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char *arcv[])
{
    pid_t id = fork();
    int n;

    if (id == 0)
    {
        int err = execlp("ping", "ping", "-c", "1", "google.com", NULL);
        if (err == -1)
        {
            printf("Could not find the program to execute\n");
            return 2;
        }
    }
    else
    {   
        int wstatus;

        wait(&wstatus);
        if (WIFEXITED(wstatus))
        {
            int statusCode = WEXITSTATUS(wstatus);
            if (statusCode == 0)
            {
                printf("Success!\n");
            } else
            {
                printf("Failure with status code %d!\n", statusCode);
            }
            
            
        }
        
        printf("Im the parent process %d, my parent is: %d\n", getpid(), getppid());
    }
 
    return 0;
}