#include <iostream>
#include <thread>

using namespace std::chrono_literals;

class background_task
{
public:
    void operator()() const
    {
        std::this_thread::sleep_for(5s);
    }
};

int main() {
    // Create a thread object and launch the thread
    background_task f;
    std::thread my_thread{f};
    // C++ most vexing parse:
    // std::thread my_thread(f())
    // Either don't use temporary object or use uniform initialization syntax

    // Wait for the thread to finish
    my_thread.join();

    std::cout << "Thread has finished." << std::endl;

    return 0;
}
