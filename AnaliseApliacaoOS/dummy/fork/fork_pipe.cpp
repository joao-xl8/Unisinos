#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

struct Data
{
    int x;
    int y;
};

int main(int argc, char *arcv[])
{
    int fd[2]; // file descriptor
    // fd[0] - read
    // fd[1] - write

    if (pipe(fd) == -1)
    {
        return 1;
    }

    pid_t id = fork();

    if (id == -1)
    {
        return 2;
    }

    wait(nullptr);
    if (id == 0)
    {
        close(fd[0]); // good practice to close one end of the pipe when using the other only
        Data sam1 = {1, 2};
        if (write(fd[1], &sam1, sizeof(Data)) == -1)
        {
            return 3;
        }
        printf("Write done Data.x: %d, Data.y: %d\n", sam1.x, sam1.y);
        close(fd[1]);
    }
    else
    {
        close(fd[1]);
        Data sam2;
        if (read(fd[0], &sam2, sizeof(Data)) == -1)
        {
            return 4;
        }
        printf("Read done Data.x: %d, Data.y: %d\n", sam2.x, sam2.y);
        sam2.x *= 2;
        printf("Manipulation with Data done Data.x: %d, Data.y: %d\n", sam2.x, sam2.y);
        close(fd[0]);
    }

    return 0;
}
