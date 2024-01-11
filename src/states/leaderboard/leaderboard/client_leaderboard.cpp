#include <iostream>

#include <client/client_handler.hpp>

#include "msg/msg_leaderboard.hpp"

#include <room/msg/msg_connection.hpp>
#include <printdebug/debugging.h>

using namespace std;


void LeaderboardState::requestGetLeaderboard(){
	GetLeaderboardMsg msg;

	ClientHandler::clientSendMsg(msg);
}

void LeaderboardState::requestBackToRoom(){
	BackToRoomMsg msg;

	ClientHandler::clientSendMsg(msg);
}

void LeaderboardState::handleRecv(const BaseMsg& msg) {
	DEBUG_PRINT("  (LeaderboardState) " + msg.toString());

	switch (msg.type()) {
		
	default:
		cerr << "CLIENT LEADERBOARD: MSG TYPE NOT INFERABLE: " << msg.toString() << endl;
	}
}