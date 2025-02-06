#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include <array>

using namespace std::literals;



int main(int argc, char *argv[]) {
    std::array<std::thread, 5> philosophers;
    std::array<bool, 5> mouthfulls = { false, false, false, false, false };
    std::array<int, 5> forks { 0, 1, 2, 3, 4};
    std::array<std::mutex, 5> fork_mtx { std::mutex(), std::mutex(), std::mutex(), std::mutex() };
    std::mutex cout_mtx;

    for (int i = 0; i < philosophers.size(); ++i) {
        philosophers[i] = std::thread([i, &cout_mtx, &fork_mtx, &mouthfulls]() {
            int lfork = i;
            int rfork = (i + 1) % 5;

            std::unique_lock<std::mutex> cout_lck(cout_mtx);
            std::cout << "philosopher " << i <<  " thinks...\n";
            cout_lck.unlock();

            std::this_thread::sleep_for(1s);

            std::scoped_lock<std::mutex, std::mutex> two_forks_mtx(fork_mtx[lfork], fork_mtx[rfork]);

            cout_lck.lock();
            std::cout << "Philosopher " << i << " takes left fork " << lfork << '\n';
            cout_lck.unlock();

            cout_lck.lock();
            std::cout << "Philosopher " << i << " takes right fork " << rfork << '\n';
            cout_lck.unlock();


            cout_lck.lock();
            std::cout << "philosopher " << i << " eats\n";
            cout_lck.unlock();

            std::this_thread::sleep_for(1s);

            mouthfulls[i] = true;

            cout_lck.lock();
            std::cout << "philosopher " << i << " done eating\n";
            cout_lck.unlock();
        });
    }

    for (auto& th : philosophers)
        th.join();

    return 0;
}
