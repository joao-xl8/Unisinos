#include <stdio.h>
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

int x = 0;
std::mutex mutex;
void routine() {
    mutex.lock();
    for (int i = 0; i < 10000000; i++)
    {
        x++;
    }
    mutex.unlock();
};

int main() {
    std::vector<std::thread> tv;
    for (int i = 0; i < 5; i++)
    {
        tv.emplace_back(std::thread(routine));
        // tv.emplace_back(routine); also works
    }

    for (auto &t: tv)
    {
        if (t.joinable())
        {
            t.join();
        }        
    }
    
    std::cout << x << std::endl;
    return 0;
}