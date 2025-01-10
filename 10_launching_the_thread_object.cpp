#include <iostream>
#include <thread>

// Function to be executed by the thread
void threadFunction() {
    std::cout << "Thread is running..." << std::endl;
}

int main() {
    // Create a thread object and launch the thread
    std::thread myThread(threadFunction);

    // Wait for the thread to finish
    myThread.join();

    std::cout << "Thread has finished." << std::endl;

    return 0;
}
