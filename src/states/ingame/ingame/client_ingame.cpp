#include <iostream>

#include <client/client_handler.hpp>

#include "msg/msg_ingame.hpp"
#include "msg/msg_next_end.hpp"

#include <room/msg/msg_connection.hpp>	// Allow other players to enter/exit in game
#include <printdebug/debugging.h>

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