#include <stdio.h>
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

int x = 0;
std::mutex mutex;
void routine()
{
    int value = 0;
    for (int i = 0; i < 10000000; i++)
        value++;
    std::lock_guard<std::mutex> g{mutex};
    x += value;
};

int main()
{
    std::vector<std::thread> tv;
    for (int i = 0; i < 5; i++)
        tv.emplace_back(routine);

    for (auto &t : tv)
    {
        if (t.joinable())
        {
            t.join();
        }
    }

    std::cout << x << std::endl;
    return 0;
}