#include <unistd.h>
#include <iostream>
#include <sys/wait.h>
#include <vector>
#include <numeric>
#include <iterator>

int main()
{
    std::vector<int> data{1, 2, 5, 3, 6, 8, 8, 2, 3, 3, 2};
    int chunk = data.size() / 3;
    int remainig = data.size() % 3;
    std::vector<int>::iterator start;
    std::vector<int>::iterator end;
    int fd[2];
    if (pipe(fd) == -1)
    {
        return 1;
    }

    pid_t pid1 = fork();
    pid_t pid2 = -2;
    if (pid1 == -1)
    {
        return 2;
    }

    if (pid1 == 0)
    {
        pid2 = fork();
        if (pid2 == -1)
        {
            return 3;
        }
        if (pid2 == 0)
        {
            // grand child first third of chunk
            start = data.begin();
            end = start + chunk + (remainig > 0 ? 1 : 0);
        }
        else
        {
            // child second third of chunk
            start = data.begin() + chunk + (remainig > 0 ? 1 : 0);
            end = start + chunk + (remainig > 1 ? 1 : 0);
        }
    }
    else
    {
        // parent last third of chunk
        start = data.end() - chunk;
        end = data.end();
    }

    std::copy(start, end, std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    int sum = std::accumulate(start, end, 0);

    if (pid1 == 0 && pid2 == 0) // in grandchild pid1 is also 0 because it copies the variables
    {
        close(fd[0]);
        if (write(fd[1], &sum, sizeof(sum)) == -1)
            return 6;
        std::cout << "Final sum from grandchild: " << sum << std::endl;
        close(fd[1]);
    }
    else if (pid1 == 0)
    {
        int sumFromGrandChild = 0;
        if (read(fd[0], &sumFromGrandChild, sizeof(sumFromGrandChild)) == -1)
            return 4;
        std::cout << "Sum from child: " << sum << std::endl;
        sum += sumFromGrandChild;
        close(fd[0]);
        if (write(fd[1], &sum, sizeof(sum)) == -1)
            return 5;
        close(fd[1]);
        std::cout << "Final sum from child: " << sum << std::endl;
        waitpid(pid2, nullptr, 0);
    }
    else
    {
        close(fd[1]);
        int sumFromChild = 0;
        if (read(fd[0], &sumFromChild, sizeof(sumFromChild)) == -1)
            return 7;
        std::cout << "Sum from parent: " << sum << std::endl;
        sum += sumFromChild;
        close(fd[0]);
        std::cout << "Final sum from parent: " << sum << std::endl;
        waitpid(pid1, nullptr, 0);
    }

    return 0;
}
