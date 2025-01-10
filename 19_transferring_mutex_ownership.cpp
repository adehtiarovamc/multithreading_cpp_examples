#include <thread>
#include <mutex>

std::mutex some_mutex;

std::unique_lock<std::mutex> get_lock(char* buff)
{
    std::unique_lock<std::mutex> lk(some_mutex);
    buff = new char[1024];
    for (int i = 0; i < 1024; ++i)
         buff[i] = 0;
    return lk;
}


int main (int argc, char *argv[]) {
    char* buff;
    auto lck = get_lock(buff);
    delete[] buff;
    return 0;
}
