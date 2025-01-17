#include <shared_mutex>
#include <thread>
#include <vector>

using namespace std::chrono_literals;

std::shared_mutex mtx;

void read_fun(std::vector<int>& data)
{
    for (int i = 0; i < 5; ++i) {
        std::shared_lock<std::shared_mutex> lk(mtx);
        if (!data.empty()) {
            // send it to the ui/over network/serialize/....
            int some_data = data.back();
        }
        std::this_thread::sleep_for(5s);
    } 
}

void write_fun(std::vector<int>& data)
{
    for (int i = 0; i < 5; ++i) {
        std::unique_lock<std::shared_mutex> lk(mtx);
        data.push_back(i);
        std::this_thread::sleep_for(10s);
    }
}


int main (int argc, char *argv[]) {
    std::vector<std::thread> read_threads;
    std::vector<int> data = { -1 };
    for (int i = 0; i < 5; ++i)
        read_threads.emplace_back(std::thread(read_fun, std::ref(data)));

    std::thread write_thread(write_fun, std::ref(data));

    for (auto &th : read_threads)
        th.join();

    write_thread.join();
    return 0;
}
