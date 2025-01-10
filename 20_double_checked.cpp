#include <mutex>

// what could possibly go wrong here?..

std::shared_ptr<char[]> resource_ptr;
std::mutex resource_mtx;

void fun()
{
    if (!resource_ptr) {
    std::unique_lock<std::mutex> lck;
        if (!resource_ptr)
        {
            resource_ptr.reset(new char[1024]);
        }
    }
    // resource_ptr->do_stuff();
}

int main (int argc, char *argv[]) {
    fun();
    return 0;
}
