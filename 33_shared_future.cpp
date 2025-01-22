#include <future>

using namespace std::chrono_literals;

void cell_formula(int val)
{
    ;
}

int main (int argc, char *argv[]) {
    std::promise<int>produced_answer;
    std::future<int> consumed_answer = produced_answer.get_future();

    std::thread producer([&produced_answer]() {
        std::this_thread::sleep_for(6s);
        produced_answer.set_value(42);
    });

    std::shared_future<int> shared_consumed_answer = consumed_answer.share();

    std::vector<std::thread> consumers;
    for (int i = 0; i < 10; ++i)
        consumers.emplace_back(std::thread([shared_consumed_answer]() {
            int answer = shared_consumed_answer.get();
            // let's asume that each thread is an excell cell with
            // formula. So the "cell" waits for other "cell" (producer)
            // to produce the value (entered by user) to calculate it's formula
            cell_formula(answer);
        }));

    producer.join();
    for (auto& consumer : consumers)
        consumer.join();

    return 0;
}
