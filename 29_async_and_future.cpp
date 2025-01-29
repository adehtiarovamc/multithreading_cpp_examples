#include <future>
#include <iostream>
#include <vcruntime_new.h>

using namespace std::chrono_literals;

int find_the_answer_to_ltuae()
{
    std::this_thread::sleep_for(10s);
    return 42;
}


int main (int argc, char *argv[]) {
    std::future<int> the_answer_to_ltuae = std::async(find_the_answer_to_ltuae); 
    std::this_thread::sleep_for(5s);
    std::cout << "The Answer to Life, the Universe, and Everything: " 
        << the_answer_to_ltuae.get() << '\n';
    return 0;
}
