#include <iostream>

#include <client/client_handler.hpp>

#include "msg/msg_ingame.hpp"
#include "msg/msg_next_end.hpp"

#include <room/client_connection.hpp>	// Allow other players to enter/exit in game
#include <printdebug/debugging.h>

using namespace std;

void InGameState::requestDraw(int playerID, int x, int y, const char* color){
	DrawMsg msg;

	msg.x = x;
	msg.y = y;
	// color+1 to skip the #
	strncpy(msg.color, color+1, 6); // Copy the color
    msg.color[7] = '\0'; // Ensure null termination

	ClientHandler::clientSendMsg(msg);
}

void InGameState::requestAnswer(int playerID, const char *answer){
	AnswerMsg msg;
	
	strncpy(msg.answer, answer, 900); // Copy the color
    // msg.answer[sizeof(msg.answer) - 1] = '\0'; // Ensure null termination

	ClientHandler::clientSendMsg(msg);
}

void InGameState:: requestScore(int playerID, int score){
	ScoreMsg msg;

	msg.playerID = playerID;
	msg.score = score;

	ClientHandler::clientSendMsg(msg);
}

void handleRoundSetting(const NextRoundMsg& msg) {
	DEBUG_PRINT(" Next round: " + to_string(msg.timer) + "s, I'm a " 
		+ (msg.role == 0 ? "guesser" : "drawer (" + string(msg.word)  + ")"));
}

void InGameState::handleRecv(const BaseMsg &msg)
{
	DEBUG_PRINT("  (InGameState) " + msg.toString());

	switch (msg.type()) {
		case MsgType::NEXT_ROUND:
			handleRoundSetting(static_cast<const NextRoundMsg&>(msg));
			break;
		case MsgType::DRAW:
			break;
		case MsgType::ANSWER:
			break;
		case MsgType::SCORE: 
			break;

		case MsgType::CONNECT:
			ClientConn::handleConnect(static_cast<const PlayerConnectMsg&>(msg), client);
			break;
		case MsgType::DISCONNECT:
			ClientConn::handleDisconnect(static_cast<const PlayerDisconnectMsg&>(msg) , client);
			break;
	default:
		cerr << "CLIENT INGAME: MSG TYPE NOT INFERABLE: " << msg.toString() << endl;
	}
}