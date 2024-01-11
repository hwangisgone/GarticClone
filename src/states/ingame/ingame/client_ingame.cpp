#include <iostream>

#include <client/client_handler.hpp>

#include "msg/msg_ingame.hpp"
#include "msg/msg_next_end.hpp"

#include <room/client_connection.hpp>	// Allow other players to enter/exit in game
#include <js_io/js_output.hpp>
#include <printdebug/debugging.h>

using namespace std;

void InGameState::requestDraw(int x, int y, const char* color){
	DrawMsg msg;

	msg.x = x;
	msg.y = y;
	// color+1 to skip the #
	strncpy(msg.color, color+1, 6); // Copy the color, skip the #
	msg.color[7] = '\0';			// Ensure null termination

	ClientHandler::clientSendMsg(msg);
}

void InGameState::requestAnswer(const char *answer){
	AnswerMsg msg;
	msg.playerID = 0;
	strncpy(msg.answer, answer, 200); // Copy the answer

	ClientHandler::clientSendMsg(msg);
}


void jsDraw(const DrawMsg &msg) {
	globalJsEval("game_draw(" + to_string(msg.x) + "," + to_string(msg.y) + ",\"#" + string(msg.color) + "\")");
}

void jsAnswer(const AnswerMsg &msg) {
	globalJsEval("game_answer(" + to_string(msg.playerID) + ",\"" + string(msg.answer) + "\")");
}

void jsScore(const ScoreMsg &msg) {
	globalJsEval("game_score(" + to_string(msg.playerID) + "," + to_string(msg.score) + ")");
}

void jsNextRound(const NextRoundMsg& msg) {
	globalJsEval("game_nextRound(" + to_string(msg.role) + "," + to_string(msg.timer) + ",\"" + string(msg.word) + "\")");
}





void handleDraw(const DrawMsg &msg) {
	TEST_PRINT("Drawn " + to_string(msg.x) + ", " + to_string(msg.y) + ", #" + string(msg.color));
	jsDraw(msg);
}

void handleAnswer(const AnswerMsg &msg, ClientHandler * client) {
	try {
		DisplayPlayer& ppp = client->playerMap.at(msg.playerID);
		TEST_PRINT(to_string(msg.playerID) + " " + string(ppp.name) + " answered:" + string(msg.answer));
		jsAnswer(msg);
	}
	catch (const std::out_of_range &e) {
		cerr << "DISPLAY PLAYER " << msg.playerID << " NOT FOUND (handleAnswer). Exception at " << e.what() << endl;
	}
}

void handleScore(const ScoreMsg &msg, ClientHandler * client) {
	try {
		DisplayPlayer& ppp = client->playerMap.at(msg.playerID);
		TEST_PRINT(to_string(msg.playerID) + " " + string(ppp.name) + " scored:" + to_string(msg.score));
		jsScore(msg);
	}
	catch (const std::out_of_range &e) {
		cerr << "DISPLAY PLAYER " << msg.playerID << " NOT FOUND (handleScore). Exception at " << e.what() << endl;
	}
}

void handleRoundSetting(const NextRoundMsg& msg) {
	DEBUG_PRINT(" Next round: " + to_string(msg.timer) + "s, I'm a " 
		+ (msg.role == 0 ? "guesser" : "drawer (" + string(msg.word)  + ")"));
	jsNextRound(msg);
}


void InGameState::handleRecv(const BaseMsg &msg)
{
	DEBUG_PRINT("  (InGameState) " + msg.toString());

	switch (msg.type()) {
		case MsgType::NEXT_ROUND:
			handleRoundSetting(static_cast<const NextRoundMsg&>(msg));
			break;
		case MsgType::DRAW:
			handleDraw(static_cast<const DrawMsg&>(msg));
			break;
		case MsgType::ANSWER:
			handleAnswer(static_cast<const AnswerMsg&>(msg), client);
			break;
		case MsgType::SCORE: 
			handleScore(static_cast<const ScoreMsg&>(msg), client);
			break;


		case MsgType::CONNECT:
			ClientConn::handleConnect(static_cast<const PlayerConnectMsg&>(msg), client);
			break;
		case MsgType::DISCONNECT:
			ClientConn::handleDisconnect(static_cast<const PlayerDisconnectMsg&>(msg) , client);
			break;
		case MsgType::BACK_TO_ROOM:
			ClientConn::backToRoom(client);
			break;
		default:
			cerr << "CLIENT INGAME: MSG TYPE NOT INFERABLE: " << msg.toString() << endl;
			break;
	}
}