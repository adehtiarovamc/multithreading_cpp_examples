#include <string>
#include <thread>

void fun(int i, const std::string& data_buff) {
    // works with data_buff
    ;
}


int main (int argc, char *argv[]) {
    std::thread t(fun, 3, "hello word");
    t.detach();
    return 0;
}
