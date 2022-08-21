// Copyright (c) Nicolas VENTER All rights reserved.

#pragma once

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <mutex>

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

private:
	std::condition_variable cv;
	std::atomic_bool bWaiting{false};
	std::atomic_bool bInterrupted{false};
};

// ============================================================
// ============================================================
// ===================== Implementations  =====================
// ============================================================
// ============================================================

InterruptibleSleep::~InterruptibleSleep() { interrupt(); }

template <class _Rep, class _Period> void InterruptibleSleep::sleepFor(const std::chrono::duration<_Rep, _Period>& _Rel_time)
{
	bInterrupted = false;
	bWaiting = true;
	std::mutex m;
	std::unique_lock<std::mutex> lock(m);
	cv.wait_for(lock, _Rel_time);
	bWaiting = false;
}

void InterruptibleSleep::interrupt()
{
	cv.notify_all();
	bInterrupted = bWaiting.load();
}

bool InterruptibleSleep::getInterrupted() const { return bInterrupted; }