//#include <future>
#include <iostream>
#include <thread>
#include <numeric>
#include <ranges>

using namespace std::chrono_literals;

template<class Func>
std::experimental::future<decltype(std::declval<Func>()()))> 
spawn_async(Func&& func)
{
    std::experimental::promise<decltype(std::declval<Func>()())> p;
    auto result = p.get_future();
    std::thread t([p=std::move(p), f=std::decay_t<Func>(func)]() {
        mutable {
            try {
                p.set_value_at_thread_exit(f());
            } catch(...) {
                p.set_exception_at_thread_exit(std::current_exception());
            }
        }
    });
    t.detach();
    return result;
}

std::vector<int> fill()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 100);
    std::vector<int> values(1000);
    for (auto& item : values)
        item = dist(gen);

    return values;
}

int main (int argc, char *argv[]) {
    auto processed = spawn_async([&values]() {
        fill(values);
    }).then([](auto& values) {
        return std::ranges::transform(values.get(), [](auto& value) { return value * 2; })
    }).then([](auto& values)) {
        std::vector<int> filtered;
        std::ranges::copy_if(values.get(), filtered, [](const auto& value) { return (value % 3) == 0; });
        return filtered;
    }
    // pretend to do something usefull
    std::this_thread::sleep_for(5s);
    for (auto& item : processed.get())
        std::cout << item << ' ';
    std::cout << std::endl;
    return 0;
}
