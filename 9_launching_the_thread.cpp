#include <iostream>
#include <thread>

class background_task
{
public:
    void operator()() const
    {
        do_something();
        do_something_else();
    }
};

int main() {
    // Create a thread object and launch the thread
    background_task f;
    std::thread my_thread{f()}
    // C++ most vexing parse:
    // std::thread my_thread(f())
    // Either don't use temporary object or use uniform initialization syntax

    // Wait for the thread to finish
    myThread.join();

    std::cout << "Thread has finished." << std::endl;

    return 0;
}
