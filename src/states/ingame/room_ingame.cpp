#include <iostream>
#include <cstring>

#include "server/room_handler.hpp"

#include "sockaddr_in/sockaddr_in_functions.h"
#include "msg/msg_sendrecv.h"
#include "states/room/msg_connection.hpp" // Allow other players to enter/exit in game
#include "msg_ingame.hpp"
#include "msg_next_end.hpp"
#include "debugging.h"

#include "database/word_list.hpp"

using namespace std;

bool checkAnswer(char *correct_ans, char *ans)
{
	return strcmp(correct_ans, ans) == 0;
}

void handleScore(const ScoreMsg &msg, int playerID, char *correct_ans, RoomHandler *room)
{
	auto i = room->playerMap.find(playerID);
	int score = 0; // TODO: fix compiler with this getPoint(correct_ans);

	if (i != room->playerMap.end())
	{
		Player targetPlayer = i->second;
		targetPlayer.currentScore += score;
	}
}


void handleAnswer(const BaseMsg &msg, int playerID, char *correct_ans, RoomHandler *room)
{
	// get answer from playerID from msg
	char *answer_from_playerID;

	// how to get boardcast function of roomhandle here

	// room->broadcastExcept(*msg, playerID);

	if (checkAnswer(correct_ans, answer_from_playerID))
	{
		handleScore(static_cast<const ScoreMsg &>(msg), playerID, correct_ans, room);
		updateWord(wordsGlobal, correct_ans, true);
		// maybe can boardcast to all that some one correct
	}
	else
	{
		//
	}
}

void startGame(const BaseMsg &msg, string wordChoose, char *ans)
{
	// msg -> answer
	// strcmp(answer, answer);
	// change Word;
	// maybe get word from the queue
	int length = wordChoose.length();
	ans = new char[length+1];
	strcpy(ans, wordChoose.c_str());
}


void InGameState::handle(const BaseMsg &msg, int playerID)
{
	DEBUG_PRINT("  (InGameState) " + msg.toString());

	unordered_map<int, Player> state_playerMap;
	state_playerMap = room->playerMap;
	auto index = state_playerMap.find(playerID);

	Word w = getRandomAndRemove(room->wordCollection);
	string wordChoose = w.word;

	switch (msg.type())
	{
	case MsgType::START_GAME:
		// start game with word choose from word collection
		startGame(static_cast<const StartMsg &>(msg), wordChoose, answer);
		break;
	case MsgType::ANSWER:
		handleAnswer(static_cast<const AnswerMsg &>(msg), playerID, answer, room);
		break;
	case MsgType::SCORE:
		handleScore(static_cast<const ScoreMsg &>(msg), playerID, answer, room);
		break;
	case MsgType::NEXT_ROUND:
		// next_round with word choose from word collection
		startGame(static_cast<const NextRoundMsg &>(msg) , string(getRandomAndRemove(room->wordCollection).word) , answer);
		break;
	default:
		cerr << "SERVER ROOM: MSG TYPE NOT INFERABLE: " << msg.toString() << endl;
	}
}