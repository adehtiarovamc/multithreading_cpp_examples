#include <thread>
#include <future>

using namespace std::chrono_literals;

class Connection
{
public:
    void process_some_data()
    {
        std::this_thread::sleep_for(5s);
        // spawn connection, wait for response, check respnse status
        result_.set_value(0);
    }

    std::promise<int>& get_promise()
    {
        return result_;
    }

private:
    std::promise<int> result_;
};

int main (int argc, char *argv[]) {
    std::vector<Connection> connections(10);
    std::vector<std::thread> connection_threads;
    std::vector<std::future<int>> futures;

    for (auto& conn : connections)
        futures.emplace_back(conn.get_promise().get_future());
    
    for (auto& conn : connections)
        connection_threads.emplace_back(std::thread(&Connection::process_some_data, &conn));

    std::vector<int> results(10);
    for (int i = 0; i < results.size(); ++i)
        results[i] = futures[i].get(); // blocking happends here

    // !as threads are still joinable, don't forget to call detach or join here!
    for (auto& thread : connection_threads)
        thread.join();

    return 0;
}
