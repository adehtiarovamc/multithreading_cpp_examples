#include <iostream>
#include <thread>
#include <mutex>

int counter = 0; // Shared counter
std::mutex mtx;  // Mutex to protect the counter

void incrementCounter() {
    for (int i = 0; i < 1000; ++i) {
        std::lock_guard<std::mutex> lock(mtx); // Lock the mutex
        ++counter;                             // Increment the counter
        // Mutex is automatically unlocked when lock goes out of scope
    }
}

int main() {
    std::thread t1(incrementCounter);
    std::thread t2(incrementCounter);

    t1.join();
    t2.join();

    std::cout << "Final counter value: " << counter << std::endl;

    return 0;
}
