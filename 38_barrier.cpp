#include <barrier>
#include <iostream>
#include <thread>
#include <vector>

using namespace std::chrono_literals;

int main (int argc, char *argv[]) {
    std::vector<std::thread> workers;
    std::barrier sync(5);
    for (int i = 0; i < 5; ++i) {
        workers.emplace_back(std::thread([i, &sync]() {
            for (int j = 0; j < 5; ++j) {
                if (i == 0)
                    std::this_thread::sleep_for(10s);
                else
                    std::this_thread::sleep_for(5s);

                if (j == 0 and i == 4) {
                    sync.arrive_and_drop();
                    return;
                }

                sync.arrive_and_wait();
            }
        }));
    }
    for (auto& worker : workers)
        worker.join();

    return 0;
}
