#include <stdexcept>
#include <thread>
#include <chrono>

void fun() {
    using namespace std::chrono_literals;
    std::thread t([]() {
        std::this_thread::sleep_for(10s);
    });
    try {
        throw std::logic_error("bad mood today");
    } catch (...) {
        t.join();
    }
    t.join();
}

int main (int argc, char *argv[]) {
    fun();
    return 0;
}
