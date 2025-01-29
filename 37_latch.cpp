#include <thread>
#include <vector>
#include <latch>
#include <future>

using namespace std::chrono_literals;

void do_first_part_of_work(int i)
{
    std::this_thread::sleep_for(2s);
}

void do_second_part_of_work(int i)
{
    std::this_thread::sleep_for(2s);
}

int main (int argc, char *argv[]) {
    std::vector<std::future<void>> threads;
    constexpr int threads_cnt = 10;
    std::latch done(threads_cnt);
    for (int i = 0; i < threads_cnt; ++i) {
        threads.push_back(std::async(std::launch::async, [&, i] {
            do_first_part_of_work(i);
            done.count_down();
            do_second_part_of_work(i);
        }));
    }
    done.wait();
    return 0;
}
