#include <mutex>

using namespace std::chrono_literals;

bool flag = false;
std::mutex mtx;

void waiting_worker()
{
    std::unique_lock<std::mutex> lk(mtx);
    while (!flag) {
        lk.unlock();
        std::this_thread::sleep_for(5s);
        lk.lock();
    }
}

int main (int argc, char *argv[]) {
    std::thread t(waiting_worker);

    std::this_thread::sleep_for(15s);
    {
        std::unique_lock<std::mutex> lk(mtx);
        flag = true;
    }

    t.join();
    return 0;
}
