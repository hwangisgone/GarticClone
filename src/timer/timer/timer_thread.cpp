#include <iostream>
#include <string>

#include "timer_thread.hpp"

// Static vars
std::set<TimeRoom> TimerThread::timer_set;
std::mutex TimerThread::timer_mutex;
std::chrono::steady_clock::time_point TimerThread::startTime;
// Static vars

void printtime(const std::string& text, std::chrono::steady_clock::time_point stamp, std::chrono::steady_clock::time_point start) {
	auto timepoint = std::chrono::duration_cast<std::chrono::milliseconds>(stamp - start).count();
	std::cerr << text << timepoint << std::endl;
}

void TimerThread::addTimer(int seconds, RoomHandler *room, int mode) {
	// get time in queue push by timestamp
	TimeRoom tr;

	tr.timestamp = std::chrono::steady_clock::now() + std::chrono::seconds(seconds);
	tr.room = room;
	tr.mode = mode;

	{
		std::lock_guard<std::mutex> lock(timer_mutex);
		timer_set.insert(tr);		
	}

	printtime("Scheduled at ", tr.timestamp, startTime);
}

void TimerThread::runTimerThread() {
	while (this->keepAlive) {
		auto currentTime = std::chrono::steady_clock::now();

		// Code here
		{
			std::lock_guard<std::mutex> lock(timer_mutex);
			
			// If larger then abort (since set are ordered by default);
			auto it = timer_set.begin();
			while(it != timer_set.end() && (*it).timestamp <= currentTime) {
				const TimeRoom& tr = (*it);
				if (tr.mode == 1) {
					if (tr.room->endGameCheck() == false) {
						tr.room->setState(new InGameState(tr.room));					
					} else {
						// Remove timer
					}
				} else if (tr.mode == 2) {
					// state ping
				} 
				printtime("Triggered timer mode " + std::to_string(tr.mode) + " at ", tr.timestamp, startTime);
				it = timer_set.erase(it);	// Auto go to next
			}  
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(500));		// Check every half a second
	}
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


