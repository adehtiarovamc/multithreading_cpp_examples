#include <execution>
#include <vector>
#include <iostream>

namespace se = std::execution;

int main (int argc, char *argv[]) {
    std::vector<int> vec{0, 1, 2, 3, 4, 5, 6, 7};
    auto sum = std::reduce(se::par, vec.begin(), vec.end(), 0);
    std::cout << "sum: " << sum << '\n'; 
    return 0;
}
