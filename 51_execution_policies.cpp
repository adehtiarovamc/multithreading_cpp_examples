#include <iostream>
#include <vector>
#include <algorithm>
#include <execution>

namespace se = std::execution;

int main (int argc, char *argv[]) {
    std::vector<int> unsorted = {5, 1, 2, 4, 3, 8, 7, 9, 6, 0};
    //std::sort(se::seq, unsorted.begin(), unsorted.end());
    std::sort(se::par, unsorted.begin(), unsorted.end());
    //std::sort(se::par_unseq, unsorted.begin(), unsorted.end());
    //std::sort(se::unseq, unsorted.begin(), unsorted.end());
    //
    for (int item : unsorted)
        std::cout << item << ' ';

    std::cout << '\n';

    return 0;
}
