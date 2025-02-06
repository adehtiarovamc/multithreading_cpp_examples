#include <iostream>
#include <vector>
#include <numeric>
#include <execution>

namespace se = std::execution;

int main (int argc, char *argv[]) {

    // 1 * 6 + 2 * 7 + 3 * 8 + 4 * 9 + 5 * 10
    std::vector<int> a{1, 2, 3, 4, 5};
    std::vector<int> b{6, 7, 8, 9, 10};

    int res = std::transform_reduce(se::par, a.begin(), a.end(), b.begin(), 0);
    std::cout << "result: " << res << '\n';
    return 0;
}
