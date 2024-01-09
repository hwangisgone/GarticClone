#include <iostream>
#include <set>
#include <chrono>
#include <mutex>
#include <thread>
#include <server/room_handler.hpp>

// struct RoomHandler {	// Use for test
// 	int why;
// };

struct TimeRoom {
	std::chrono::steady_clock::time_point timestamp;
	int mode;
	RoomHandler *room;

	bool operator< (const TimeRoom& tr) const {
		return timestamp < tr.timestamp;
	}
};

class TimerThread {
private:
	static std::set<TimeRoom> timer_set;
	static std::mutex timer_mutex;

	static std::chrono::steady_clock::time_point startTime;

	// std::mutex mutex;
	// std::condition_variable conditionVariable;
	bool keepAlive;  // may multithreadnig error
	std::thread thread;

public:
	static void addTimer(int seconds, RoomHandler* room , int mode);

	TimerThread() {
		// Start the thread upon object creation
		keepAlive = true;
		thread = std::thread(&TimerThread::runTimerThread, this);

		startTime = std::chrono::steady_clock::now();
		std::cerr << "Timer Thread created" << std::endl;
	}

	~TimerThread() {
		// Make sure the thread is stopped before destroying the object
		keepAlive = false;

		// Wait for the thread to finish
		if (thread.joinable()) {
			thread.join();
		}

		std::cerr << "Timer Thread destroyed" << std::endl;
	}

	void runTimerThread();
};



