// interruptJthread.cpp

#include <thread>
#include <chrono>
#include <iostream>
#include <condition_variable>

using namespace::std::literals;

int main(){
    std::jthread jth([](std::stop_token token) {
        for (int i = 0; i < 15; ++i) {
            std::this_thread::sleep_for(500ms);
            std::cout << "i: " << i << '\n';
            if (token.stop_requested())
                return;
        }
    });

    std::this_thread::sleep_for(1s);
    jth.request_stop();
}
