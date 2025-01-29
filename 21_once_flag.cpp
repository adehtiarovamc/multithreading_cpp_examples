#include <mutex>
#include <vector>

std::shared_ptr<char[]> resource_ptr;
std::once_flag resource_flag;

void init_resource()
{
    resource_ptr.reset(new char[1024]);
}

void fun()
{
    std::call_once(resource_flag, init_resource);
    // resource_ptr->do_stuff();
}

int main (int argc, char *argv[]) {
    std::vector<std::thread> threads(10);
    for (int i = 0; i < 10; ++i)
        threads.emplace_back(fun);

    for (auto& thread : threads)
        thread.join();

    return 0;
}
