#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

int x = 0;
int y = 0;
std::mutex mtx1;
std::mutex mtx2;
void routine()
{
    int value = 0;
    for (int i = 0; i < 100; i++)
        value++;
    std::unique_lock<std::mutex> lock1 {mtx1, std::defer_lock};
    std::unique_lock<std::mutex> lock2 {mtx2, std::defer_lock};
    std::lock(lock1, lock2); // lcoks can be removed if use std::scoped_lock lock(mtx1, mtx2);
    // you cant acquire in other way, becacuse it will deadlock it self when other thread
    // acquire one of the two locks faster.
    x += value;
    y += x + y;
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
    std::cout << y << std::endl;
    return 0;
}