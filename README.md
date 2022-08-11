# Interruptible Sleep

# Description

InterruptibleSleep is a **single header c++ library** that allows you to **sleep for a specified amount of time** with the ability to **interrupt the sleep at any time**.

# Installation

Include the file [`InterruptibleSleep.hpp`](InterruptibleSleep.hpp) in your project.

c++11 or later compilation required.
No external dependencies.

# Example

```cpp
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
```

Output:
```
Press enter to interrupt...
Sleeping for 3 seconds...

Interrupted!
```
*or*
```
Press enter to interrupt...
Sleeping for 3 seconds...
Done!
```

# Usage

```cpp	
struct InterruptibleSleep
{
	// destructor interrupts sleep
	~InterruptibleSleep();

	// sleeping for the specified amount of time
	template <class _Rep, class _Period> void sleepFor(const std::chrono::duration<_Rep, _Period>& _Rel_time);

	// immediately interrupt the sleep
	void interrupt();

	// true only if interrupted while waiting
	bool getInterrupted() const;
};
```

# Licence

MIT Licence. See [LICENSE file](LICENSE).
Please refer me with:

	Copyright (c) Nicolas VENTER All rights reserved.
