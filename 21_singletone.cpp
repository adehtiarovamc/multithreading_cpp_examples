
char* get_some_global_data()
{
    static char* data_holder = new char[1024];
    return data_holder;
}

int main (int argc, char *argv[]) {
    auto data_ptr = get_some_global_data();
    delete[] data_ptr;
    return 0;
}
