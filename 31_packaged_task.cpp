#include <future>
#include <iostream>
#include <chrono>

using namespace std::literals;

int main()
{
	std::packaged_task<int(int, int)> ptask([](int a, int b) {
		std::this_thread::sleep_for(2s);
		return a + b;
		});

	std::future<int> fut = ptask.get_future();

	ptask(6, 7);

	std::cout << "Waiting for result\n";

	// Call get() to receive the result of the packaged task
	std::cout << "6 + 7 is " << fut.get() << '\n';
}
