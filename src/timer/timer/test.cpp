#include <iostream>
#include <chrono>
#include <thread>
#include "TimerThread.hpp"



int main() {
	// Create the TimerThread, which starts the thread
{	
	TimerThread lobbyTimer;

	TimerThread::addTimer(5, nullptr, 1);
	TimerThread::addTimer(15, nullptr, 1);
	TimerThread::addTimer(10, nullptr, 1);
	TimerThread::addTimer(27, nullptr, 2);
	TimerThread::addTimer(19, nullptr, 1);
	TimerThread::addTimer(15, nullptr, 1);
	TimerThread::addTimer(15, nullptr, 2);
	TimerThread::addTimer(15, nullptr, 1);

	// Destroy after 35 seconds
	std::this_thread::sleep_for(std::chrono::seconds(35));
}

	std::cout << "Ended" << std::endl;

	return 0;
}