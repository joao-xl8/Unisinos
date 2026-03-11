#include <stdio.h>
#include <iostream>
#include <thread>

void func1() {};
void func2(int param1) {
    param1++;
    std::cout << param1 << std::endl;
    std::cout << std::this_thread::get_id() << std::endl;
};


int main() {
    std::thread t1{func1};
    std::thread t2{func2, 2};
    t2.join();
    t1.join();
}