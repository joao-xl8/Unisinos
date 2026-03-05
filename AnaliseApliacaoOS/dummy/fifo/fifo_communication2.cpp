#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <array>
#include <time.h>
#include <numeric>

int main()
{
    std::array<int, 5> arr;

    int fd = open("fifo_sum", O_RDONLY);
    if (fd == -1)
        return 2;

    for (int i = 0; i < arr.size(); i++)
    {
        if (read(fd, &arr[i], sizeof(arr[i])) == -1)
            return 3;
        std::cout << "Read: " << arr[i] << std::endl;
    }
    close(fd);

    int sum = std::accumulate(arr.begin(), arr.end(), 0);

    int fd2 = open("fifo_sum", O_WRONLY);
    if (fd2 == -1)
        return 4;

    if (write(fd2, &sum, sizeof(sum)) == -1)
        return 5;
    std::cout << "Wrote sum: " << sum << std::endl;

    close(fd2);
    return 0;
}