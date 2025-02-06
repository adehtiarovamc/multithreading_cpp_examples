#include <execution>
#include <iostream>
#include <vector>
#include <algorithm>

namespace se = std::execution;

// try exclusive scan here

int main (int argc, char *argv[]) {
    std::vector<int> vec{0, 1, 2, 3, 4, 5, 6, 7};
    std::vector<int> dst(vec.size());
    

    std::inclusive_scan(se::par, vec.begin(), vec.end(), dst.begin());

    for (int item : dst)
        std::cout << item << ' ';
    std::cout << '\n';
}

