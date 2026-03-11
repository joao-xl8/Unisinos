#include <thread>

struct guarded_thread : std::thread {
    using std::thread::thread;
    using std::thread::operator=;
    ~guarded_thread() { if(joinable()) join(); }
};

void f() {};
void g() {};

struct Foo
{
    int data;
};


int main() {
    guarded_thread t1{f};
    guarded_thread t2;

    if (true)
    {
        std::thread t3{g};
        t2 = std::move(t3);
    }
    
    Foo x {20}; // might throw error for example
    // with guarded we make sure that both threads are joined 
    // t1.join();
    // t2.join();
    return 0;
}
