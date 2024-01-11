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
	int roomID;

	bool operator< (const TimeRoom& tr) const {
		return timestamp < tr.timestamp;
	}
};

class TimerThread {
private:
	static std::set<TimeRoom> timer_set;
	static std::mutex timer_mutex;

	static std::chrono::steady_clock::time_point startTime;

	static std::unordered_map<int, RoomHandler *> * allRooms;
	// std::mutex mutex;
	// std::condition_variable conditionVariable;
	bool keepAlive;  // may multithreadnig error
	std::thread thread;
public:
	static void addTimer(int seconds, int roomID, int mode);
	static void removeRoomTimers(int roomID);
	static void eraseRoom(int roomID);


	TimerThread(std::unordered_map<int, RoomHandler *> * lobbyRooms){
		if (lobbyRooms == nullptr) {
			std::cerr << "Cannot init Timer Thread" << std::endl;
			return;
		}
		allRooms = lobbyRooms; // only set once
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



