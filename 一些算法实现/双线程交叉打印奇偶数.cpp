#include <thread>
#include <iostream>
#include <mutex>
#include <condition_variable>

std::mutex data_mutex;
std::condition_variable data_var;
bool label = false;

void printodd()
{
	std::unique_lock<std::mutex> ulock(data_mutex);
	for (int odd = 1; odd <= 100; odd += 2)
	{
		data_var.wait(ulock, [] {return label; });
		std::cout << std::this_thread::get_id() << ": " << odd << std::endl;
		label = false;
		data_var.notify_one();
	}
}

void printeven()
{
	std::unique_lock<std::mutex> ulock(data_mutex);
	for (int even = 0; even < 100; even += 2)
	{
		std::cout << std::this_thread::get_id() << ": " << even << std::endl;
		data_var.notify_one();
		label = true;
		data_var.wait(ulock, [] {return !label; });
	}
}

int main()
{
	std::thread t1(printeven);
	std::thread t2(printodd);
	t1.join();
	t2.join();
	std::cout << "end!" << std::endl;
	return 0;

	system("pause");
}
