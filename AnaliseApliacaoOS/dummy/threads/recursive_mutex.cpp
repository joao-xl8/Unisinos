#include <mutex>
#include <thread>
#include <iostream>
#include <list>

// this call will deadlock itself because it calls recursivelly the mutex. so Instead of mutex we use recursive mutex.

std::recursive_mutex cout_mutex; 
template<typename Arg, typename... Args>
void write(Arg a, Args... tail) {
    cout_mutex.lock();
    std::cout << a;
    write(tail...);
    cout_mutex.unlock();
}

int main() {
    write("Hello,", " World!"); // if a thread calls this will not throw deadlock
    return 0;
}