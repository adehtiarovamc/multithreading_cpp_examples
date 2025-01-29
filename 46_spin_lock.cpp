#include <atomic>
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

class SpinLockMutex
{
public:
    void lock()
    {
        while (flag_.test_and_set(std::memory_order_acquire));
    }

    void unlock()
    {
        flag_.clear(std::memory_order_release);
    }

private:
    std::atomic_flag flag_ = ATOMIC_FLAG_INIT;
};

int main (int argc, char *argv[]) {
    std::vector<std::thread> threads;
    SpinLockMutex mtx;
    for (int i = 0; i < 10; ++i)
        threads.emplace_back([i, &mtx]() {
            std::lock_guard<SpinLockMutex> lck(mtx);
            std::cout << "Thread # " << i << '\n';
        });

    for (auto& th : threads)
        th.join();

    return 0;
}
