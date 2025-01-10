#include <thread>
#include <vector>
#include <string>

struct data
{
    std::string name_;
    std::vector<std::string> values_;
};

void fun(data& data_ref)
{
    // modify data by reference
    ;
}

int main (int argc, char *argv[]) {
    data d{.name_ = "Student group", .values_ = { "Markus", "Daniel", "Tim", "Volfgang" }};
    std::thread t(fun, std::ref(d));
    return 0;
}
