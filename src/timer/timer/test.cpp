#include <iostream>
#include <chrono>
#include <thread>
#include "TimerThread.hpp"



int main() {
	// Create the TimerThread, which starts the thread
{	
	TimerThread lobbyTimer;

	TimerThread::addTimer(5, 99, 1);
	TimerThread::addTimer(15, 99, 1);
	TimerThread::addTimer(10, 99, 1);
	TimerThread::addTimer(27, 99, 2);
	TimerThread::addTimer(19, 99, 1);
	TimerThread::addTimer(15, 99, 1);
	TimerThread::addTimer(15, 99, 2);
	TimerThread::addTimer(15, 99, 1);

	// Destroy after 35 seconds
	std::this_thread::sleep_for(std::chrono::seconds(35));
}

	std::cout << "Ended" << std::endl;

	return 0;
}