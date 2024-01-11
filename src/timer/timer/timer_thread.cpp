#include <iostream>
#include <string>

#include "timer_thread.hpp"

// Static vars
std::set<TimeRoom> TimerThread::timer_set;
std::mutex TimerThread::timer_mutex;
std::chrono::steady_clock::time_point TimerThread::startTime;
std::unordered_map<int, RoomHandler *> * TimerThread::allRooms = nullptr;
// Static vars

void printtime(const std::string& text, std::chrono::steady_clock::time_point stamp, std::chrono::steady_clock::time_point start) {
	auto timepoint = std::chrono::duration_cast<std::chrono::milliseconds>(stamp - start).count();
	std::cerr << text << timepoint;
}

void TimerThread::addTimer(int seconds, int roomID, int mode) {
	// get time in queue push by timestamp
	TimeRoom tr;

	tr.timestamp = std::chrono::steady_clock::now() + std::chrono::seconds(seconds);
	tr.roomID = roomID;
	tr.mode = mode;

	{
		std::lock_guard<std::mutex> lock(timer_mutex);
		timer_set.insert(tr);		
	}

	printtime("Scheduled at ", tr.timestamp, startTime); std::cerr << std::endl;
}

void TimerThread::removeRoomTimers(int roomID) {
	{
		std::lock_guard<std::mutex> lock(timer_mutex);
		auto it = timer_set.begin();
		while (it != timer_set.end()) {
			if (it->roomID == roomID) {
				printtime("Timer removed: ", it->timestamp, startTime); std::cerr << std::endl;
				it = timer_set.erase(it);
			} else {
				++it;
			}
		}
	}
}

void TimerThread::eraseRoom(int roomID) {
	auto result = allRooms->erase(roomID);
	// Check if the removal was successful
	if (result == 1) {
		DEBUG_PRINT("> Timer: Remove room " + std::to_string(roomID) + " successful!");
	} else {
		DEBUG_PRINT("> Timer: Remove room " + std::to_string(roomID) + " failed. Not found.");
	}
}

void timerHandleState(int mode, RoomHandler * room) {
	if (mode == 1) {
		if (room->endGameCheck() == false) {
			room->setState(new InGameState(room));					
		} else {
			std::cout << "END GAME!" << std::endl;
			room->setState(new LeaderboardState());
		}
	} else if (mode == 2) {
		// state ping
	} 
}

void TimerThread::runTimerThread() {
	while (this->keepAlive) {
		auto currentTime = std::chrono::steady_clock::now();

		// Code here
	
		// If larger then abort (since set are ordered by default);
		auto it = timer_set.begin();
		while(it != timer_set.end() && (*it).timestamp <= currentTime) {
			const TimeRoom& tr = (*it);

			auto roomfind = allRooms->find(tr.roomID);
			if (roomfind != allRooms->end()) {
				timerHandleState(tr.mode, roomfind->second);
			} else {
				std::cerr << "!!! Room does not exist anymore? !!!" << std::endl;
			}

			printtime("Triggered timer mode " + std::to_string(tr.mode) + " at ", tr.timestamp, startTime); std::cerr << std::endl;
			{
				std::lock_guard<std::mutex> lock(timer_mutex);
				it = timer_set.erase(it);	// Remove timer. Set iterator to next
			}  
		}

		printtime("\rTimer: ", currentTime, startTime); std::cerr << " ";
		std::this_thread::sleep_for(std::chrono::milliseconds(500));		// Check every half a second
	}

	std::cerr << "Timer died for some reason?" << std::endl;
}

// Debug
// auto elapsedTime2 = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();
// std::cout << "Etime2: " << elapsedTime2 << std::endl;
// debug
// auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();
// std::cout << "Current elapsed time: " << elapsedTime << " milliseconds.";
// Calculate the remaining time until the next second
// auto elapsedSec = elapsedTime % 1000;
// auto remainingTime = (elapsedSec < 500) ? 500 - elapsedSec : 1000 - elapsedSec;
// std::this_thread::sleep_for(std::chrono::milliseconds(remainingTime);


