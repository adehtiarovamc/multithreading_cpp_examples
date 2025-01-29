#include <future>
#include <iostream>
#include <stdexcept>

double square_root(double x)
{
    if (x < 0)
        throw std::out_of_range("x < 0");

    return sqrt(x);
}

int main (int argc, char *argv[]) {
    std::future<double> f = std::async(square_root, -1);

    try { 
        double result = f.get();
    } catch (const std::out_of_range& err) {
        std::cout << err.what() << '\n';
    }
    return 0;
}

