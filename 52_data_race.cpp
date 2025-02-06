#include <algorithm>
#include <vector>
#include <iostream>
#include <execution>

namespace se = std::execution;

int main (int argc, char *argv[]) {
    std::vector<int> vec(10'000);
    int count = 0;

    std::for_each(se::par, vec.begin(), vec.end(), [&count](int& x) {
        x = ++count;
    });

    for (auto i : vec)
        std::cout << i << ' ';
    std::cout << std::endl;
    
    return 0;
}
