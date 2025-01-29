#include <future>
#include <iostream>
#include <stdexcept>

void square_root(double x, std::promise<double>& promise)
{
    try {
        if (x < 0)
            throw std::out_of_range("x < 0");

        promise.set_value(sqrt(x));

    } catch (const std::out_of_range& err) {
        promise.set_exception(std::current_exception());
    }
}

int main (int argc, char *argv[]) {
    std::promise<double> promise;
    std::future<double> fut = promise.get_future();
    std::thread th = std::thread(&square_root, -1, std::ref(promise));

    try { 
        double result = fut.get();
    } catch (const std::out_of_range& err) {
        std::cout << err.what() << '\n';
    }

    th.join();
    return 0;
}

