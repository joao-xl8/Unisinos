#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <chrono>

std::mutex mtx;
std::condition_variable fuel_cv;
int fuel = 0;

void fuel_filling() {
    for (int i = 0; i < 5; i++)
    {   
        // scoped to free the mutex fast as possible
        {
            std::lock_guard<std::mutex> lock(mtx);
            fuel += 15;
            std::cout << "Filling fuel. Current fuel : " << fuel << std::endl;
        }
        fuel_cv.notify_one();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    
}
void car() {
    std::unique_lock<std::mutex> lock(mtx);
    fuel_cv.wait(lock, [] { 
        std::cout << "Not enought fuel" << std::endl;
        return fuel > 40; 
    });
    fuel -= 40;
    std::cout << "Car filled. Current fuel : " << fuel << std::endl;
}

int main()
{
    std::vector<std::thread> tv;
    for (int i = 0; i < 2; i++) {
        if (i == 1)
        {
            tv.emplace_back(fuel_filling);
        } else
        {
            tv.emplace_back(car);
        }
    }

    for (auto &t : tv) t.join();
  

    return 0;
}