#include <iostream>

#include "client/client_handler.hpp"

#include "msg_leaderboard.hpp"
#include "debugging.h"

using namespace std;


void LeaderboardState::handleRecv(const BaseMsg& msg) {
	DEBUG_PRINT("  (LeaderboardState) " + msg.toString());

	switch (msg.type()) {

	default:
		cerr << "CLIENT LEADERBOARD: MSG TYPE NOT INFERABLE: " << msg.toString() << endl;
	}
}