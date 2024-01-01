#include <iostream>

#include "client/client_handler.hpp"

#include "states/room/msg_connection.hpp"	// Allow other players to enter/exit in game
#include "msg_ingame.hpp"
#include "msg_next_end.hpp"
#include "debugging.h"

using namespace std;



void InGameState::handleRecv(const BaseMsg &msg)
{
	DEBUG_PRINT("  (InGameState) " + msg.toString());

	switch (msg.type()) {
		case MsgType::DRAW:
			break;
		case MsgType::ANSWER:
			break;
		case MsgType::SCORE: 
			break;
		case MsgType::CONNECT:
			break;
		case MsgType::DISCONNECT:
			break;
	default:
		cerr << "CLIENT INGAME: MSG TYPE NOT INFERABLE: " << msg.toString() << endl;
	}
}