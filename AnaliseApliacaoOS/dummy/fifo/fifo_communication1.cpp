#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <array>
#include <time.h>

int main()
{
    if (mkfifo("fifo_sum", 0777) == -1)
    {
        if (errno != EEXIST)
        {
            std::cout << "Could not create fifo_communication1 file" << std::endl;
            return 1;
        }
    }

    std::array<int, 5> arr;
    srand(time(nullptr));
    for (int i = 0; i < arr.size(); i++)
    {
        arr[i] = rand() % 100;
    }

    int fd1 = open("fifo_sum", O_WRONLY);
    if (fd1 == -1)
        return 2;

    for (int i = 0; i < arr.size(); i++)
    {
        if (write(fd1, &arr[i], sizeof(int)) == -1)
            return 3;
        std::cout << "Wrote: " << arr[i] << std::endl;
    }

    close(fd1);

    int fd2 = open("fifo_sum", O_RDONLY);
    if (fd2 == -1)
        return 4;

    int sum;
    if (read(fd2, &sum, sizeof(sum)) == -1)
        return 5;
    std::cout << "Read sum: " << sum << std::endl;
    close(fd2);
    return 0;
}