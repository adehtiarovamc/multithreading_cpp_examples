#include <mutex>

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
    fun();
    return 0;
}
