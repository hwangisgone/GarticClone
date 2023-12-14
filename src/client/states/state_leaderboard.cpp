#include <iostream>

#include "msg/msg_format.hpp"

#include "debugging.h"
#include "client_handler.hpp"

using namespace std;


void LeaderboardState::handleRecv(const BaseMsg& msg) {
	DEBUG_PRINT("  (LeaderboardState) " + msg.toString());

	switch (msg.type())
	{
	default:
		cerr << "CLIENT LEADERBOARD: MSG TYPE NOT INFERABLE: " << msg.toString() << endl;
	}
}