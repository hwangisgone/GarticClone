#include <iostream>
#include <cstring>
#include <random>
#include <vector>
#include <server/room_handler.hpp>

#include "msg/msg_ingame.hpp"
#include "msg/msg_next_end.hpp"

#include <msg/msg_sendrecv.h>

#include <room/room_connection.hpp> // Allow other players to enter/exit in game
#include <printdebug/debugging.h>
#include <database/word_list.hpp>
#include <utils/rng.hpp>

using namespace std;

InGameState::InGameState(RoomHandler * room) {	// Initialize a new game
	this->setHandler(room);	// Required, otherwise segmentation fault

	WordHanlder *wh = room->handlerWord;
	this->answer = wh->getRandomAndRemove(wh->wordCollection);
	
	// Get random playerID from the map
	std::uniform_int_distribution<size_t> dist(0, room->playerMap.size() - 1);
	size_t randomIndex = dist(gameRng);		// Iterate to the random index to get the corresponding key
	auto it = std::next(room->playerMap.begin(), randomIndex);

	DEBUG_PRINT("This round word: '" + string(this->answer.word) + "'");
	this->drawerID = it->first;
	// Get random playerID from the map
	// Choose as player to draw

	NextRoundMsg nextmsg;
	nextmsg.timer = 30;
	nextmsg.role = 0;
	room->broadcastExcept(nextmsg, this->drawerID);

	nextmsg.role = 1;
	strncpy(nextmsg.word, this->answer.word, sizeof(this->answer.word));
	Player drawerPlayer = room->playerMap.at(drawerID);
	sendMsg(room->sockfd, (struct sockaddr*)&drawerPlayer.currentAddr, sizeof(drawerPlayer.currentAddr), nextmsg);
}


bool checkAnswer(const char *correct_ans, const char *ans)
{
	return strcmp(correct_ans, ans) == 0;
}

void handleScore(const ScoreMsg &msg, int playerID, char *correct_ans, RoomHandler *room)
{
	auto i = room->playerMap.find(playerID);
	WordHanlder *wh = room->handlerWord;
	int score = wh->getPoint(correct_ans); // TODO: fix compiler with this getPoint(correct_ans);

	if (i != room->playerMap.end())
	{
		Player targetPlayer = i->second;
		targetPlayer.currentScore += score;
	}
}


void handleAnswer(const AnswerMsg &msg, int playerID, Word correct_ans, RoomHandler *room)
{

	AnswerMsg answermsg;
	answermsg.playerID = playerID;
	room->broadcastExcept(answermsg, playerID);


	char answer_client[900];
	strcpy(answer_client, msg.answer);

	// if (checkAnswer(correct_ans, answer_client))
	// {
	// 	ScoreMsg scoreMsg;
	// 	scoreMsg.playerID = playerID;
	// 	scoreMsg.score = getPoint(words, correct_ans);
	// 	handleScore(static_cast<const ScoreMsg &>(scoreMsg), playerID, correct_ans, room, words);
	// 	updateWord(wordsGlobal, correct_ans, true);

	// 	// maybe can boardcast to all that some one correct
	// 	room->broadcastExcept(scoreMsg, playerID);
		
	// }
	// else
	// {
	// 	// something happen ??
	// }		
}


void InGameState::handle(const BaseMsg &msg, int playerID) {
	DEBUG_PRINT("  (InGameState) " + msg.toString());

	// unordered_map<int, Player> state_playerMap;
	// state_playerMap = room->playerMap;
	// auto index = state_playerMap.find(playerID);


	switch (msg.type())
	{
		case MsgType::JOIN_ROOM: {
			RoomConn::handleConnect(static_cast<const JoinRoomMsg&>(msg), playerID, room);
			break;
		}
		case MsgType::DISCONNECT: {
			RoomConn::handleDisconnect(playerID, room);
			break;
		}

		case MsgType::DRAW: {
			if (playerID == this->drawerID) {
				TEST_PRINT("  (InGameState) Drawing...");
				DrawMsg newmsg = static_cast<const DrawMsg&>(msg);
				room->broadcastExcept(newmsg, playerID);
			} else {
				TEST_PRINT("  (InGameState) Non-Drawer attempted to draw????");
			}
		}
		// case MsgType::SCORE: {	// ANSWER send score
		// 	handleScore(static_cast<const ScoreMsg &>(msg), playerID, answer, room, wordsGlobal);
		// 	break;		
		// }
		case MsgType::ANSWER: {	// Send score here if correct
			if (playerID != this->drawerID) {
				handleAnswer(static_cast<const AnswerMsg &>(msg), playerID, answer, room);
			} else {
				TEST_PRINT("  (InGameState) Drawer attempted to answer????");
			}
			break;
		}
			// next_round with word choose from word collectionstartGame
		default:
			cerr << "GAME ROOM: MSG TYPE NOT INFERABLE: " << msg.toString() << endl;
			break;
	}
}