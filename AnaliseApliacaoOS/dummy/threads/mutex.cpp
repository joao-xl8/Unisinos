#include <mutex>
#include <thread>
#include <iostream>
#include <list>

std::mutex cout_mutex; // represent the right to use mutex

template<typename Arg1, typename Arg2, typename Arg3>
void write(Arg1 arg1, Arg2 arg2 = {}, Arg3 arg3 = {}) {
    std::thread::id name = std::this_thread::get_id();
    cout_mutex.lock();
    std::cout << "Fromn thread " << name << ": " << arg1 << arg2 << arg3;
    cout_mutex.unlock();
}

struct Work {
    int jobID;
};
extern std::mutex wqm;
extern std::list<Work> wq;

void composer() {
    std::list<Work> w_requests;

    // recieve work requests while cant acquire the mutex, dont hang.
    while(true) {
        for (int i = 0; i != 10; i++)
        {
            Work w;
            // workstuff...
            w_requests.push_back(w);
        }
        if (wqm.try_lock())
        {
            wq.splice(wq.end(), w_requests);
            wqm.unlock();
        }
    }
}

int main() {

    return 0;
}