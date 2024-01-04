#include <iostream>

#include <client/client_handler.hpp>

#include "msg/msg_ingame.hpp"
#include "msg/msg_next_end.hpp"

#include <room/msg/msg_connection.hpp>	// Allow other players to enter/exit in game
#include <printdebug/debugging.h>

using namespace std;

void handleConnect(const PlayerConnectMsg& msg, ClientHandler * client) {
	DEBUG_PRINT("  (StateRoom) Connection from " + std::string(msg.name));
	client->addPlayer(msg.playerID, msg.name);
}

void handleDisconnect(const PlayerDisconnectMsg& msg, ClientHandler * client) {
	DEBUG_PRINT("  (StateRoom) Disconnection.");
	client->removePlayer(msg.playerID);
}

void InGameState::requestDraw(int playerID, int x, int y, const char* color){
	DrawMsg msg;

	msg.x = x;
	msg.y = y;
	strncpy(msg.color, color, sizeof(msg.color) - 1); // Copy the color
    msg.color[sizeof(msg.color) - 1] = '\0'; // Ensure null termination

	ClientHandler::clientSendMsg(msg);
}

void InGameState::requestAnswer(int playerID, const char *answer){
	AnswerMsg msg;
	
	strncpy(msg.answer, answer, sizeof(msg.answer) - 1); // Copy the color
    msg.answer[sizeof(msg.answer) - 1] = '\0'; // Ensure null termination

	ClientHandler::clientSendMsg(msg);
}

void InGameState:: requestScore(int playerID, int score){
	ScoreMsg msg;

	msg.score = score;

	ClientHandler::clientSendMsg(msg);
}

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
			handleConnect(static_cast<const PlayerConnectMsg&>(msg), client);
			break;
		case MsgType::DISCONNECT:
			handleDisconnect(static_cast<const PlayerDisconnectMsg&>(msg) , client);
			break;
	default:
		cerr << "CLIENT INGAME: MSG TYPE NOT INFERABLE: " << msg.toString() << endl;
	}
}