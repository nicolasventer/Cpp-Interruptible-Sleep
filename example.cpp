#include <chrono>
#include <iostream>
#include <thread>

#include "InterruptibleSleep.hpp"

int main(int argc, char const* argv[])
{
	using namespace std::chrono_literals;

	InterruptibleSleep sleep;
	std::thread t1(
		[&sleep]()
		{
			std::cout << "Sleeping for 3 seconds..." << std::endl;
			sleep.sleepFor(3s);
			if (!sleep.getInterrupted()) std::cout << "Done!" << std::endl;
		});
	std::cout << "Press enter to interrupt..." << std::endl;
	std::cin.get();
	sleep.interrupt();
	if (sleep.getInterrupted()) std::cout << "Interrupted!" << std::endl;
	if (t1.joinable()) t1.join();
	return 0;
}
