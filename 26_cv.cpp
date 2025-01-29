#include <mutex>

using namespace std::chrono_literals;

std::condition_variable cv;
std::mutex mtx;
bool flag = false;

void waiting_worker()
{
    std::unique_lock<std::mutex> lk(mtx);
    cv.wait(lk, []() { return flag; });
}

int main (int argc, char *argv[]) {
    std::thread t(waiting_worker);

    std::this_thread::sleep_for(15s);
    {
        std::unique_lock<std::mutex> lk(mtx);
        flag = true;
        cv.notify_one();
    }

    t.join();
    return 0;
}
