#include <experimental/barrier>
#include <iostream>
#include <thread>
#include <vector>

using namespace std::chrono_literals;

int main (int argc, char *argv[]) {
    std::vector<std::thread> workers;
    std::flex_barrier sync(5, []() {
        // some serial processing
        std::this_thread::sleep_for(5s);
        std::cout << "Processed \n";
        return -1;
    });
    for (int i = 0; i < 5; ++i) {
        workers.emplace_back(std::thread([i, &sync]() {
            for (int j = 0; j < 4; ++j) {
                std::this_thread::sleep_for(5s);
                sync.arrive_and_wait();
            }
        }));
    }
    for (auto& worker : workers)
        worker.join();

    return 0;
}
