#include <iostream>
#include <cstring>

#include "server/room_handler.hpp"

#include "sockaddr_in/sockaddr_in_functions.h"
#include "msg/msg_sendrecv.h"
#include "states/room/msg_connection.hpp" // Allow other players to enter/exit in game
#include "msg_ingame.hpp"
#include "msg_next_end.hpp"
#include "debugging.h"
#include "word_list.hpp"

using namespace std;

bool checkAnswer(char *correct_ans, char *ans)
{
	return strcmp(correct_ans, ans) == 0;
}

void boardcast(const BaseMsg &msg, int playerID, RoomHandler *room)
{
	auto find_addr = room->playerMap.find(playerID);
	sockaddr_in send_addr = find_addr->second.currentAddr;

	for (auto &pair : room->playerMap)
	{
		Player &player = pair.second;
		sockaddr_in to_boardcast_addr = player.currentAddr;
		if (!compareSockAddrIn(send_addr, to_boardcast_addr))
		{
			// send_msg
		}
	}
}

int add_score(int percentageWord, char *correct_ans)
{

	if (percentageWord <= 30)
		return 10;
	else if (percentageWord >= 50 && percentageWord < 80)
		return 30;
	else
		return 50;
	// check correct_answer in what level ( easy, middile, hard ) to add score
}

void handleScore(const ScoreMsg &msg, int playerID, char *correct_ans, RoomHandler *room, int statisticPercent)
{
	auto i = room->playerMap.find(playerID);
	int score = add_score(statisticPercent, correct_ans);
	if (i != room->playerMap.end())
	{
		Player targetPlayer = i->second;
		targetPlayer.currentScore += score;
	}
}

void handleWord(unordered_map<string, Statistic> &map, char *correct_ans, bool check_ans)
{
	map[correct_ans].totalCount++;
	if (check_ans == true)
	{
		map[correct_ans].successCount++;
	}
}

void handleAnswer(const BaseMsg &msg, int playerID, char *correct_ans, RoomHandler *room, unordered_map<string, Statistic> &map, int statisticPercent)
{
	char *answer;

	boardcast(msg, playerID, room);

	if (checkAnswer(correct_ans, answer))
	{
		handleScore(static_cast<const ScoreMsg &>(msg), playerID, correct_ans, room, statisticPercent);
		handleWord(map, correct_ans, true);
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

	vector<string> wordCollection = room->wordCollection;

	int statisticPercent = percentageWord(answer);

	switch (msg.type())
	{
	case MsgType::START_GAME:
		// start game with word choose from word collection
		startGame(static_cast<const StartMsg &>(msg), getRandomString(room->wordCollection), answer);
		break;
	case MsgType::ANSWER:
		handleAnswer(static_cast<const AnswerMsg &>(msg), playerID, answer, room, statisticWord, statisticPercent);
		break;
	case MsgType::SCORE:
		handleScore(static_cast<const ScoreMsg &>(msg), playerID, answer, room, statisticPercent);
		break;
	case MsgType::NEXT_ROUND:
		// next_round with word choose from word collection
		startGame(static_cast<const NextRoundMsg &>(msg) , getRandomString(room->wordCollection), answer);
		break;
	default:
		cerr << "SERVER ROOM: MSG TYPE NOT INFERABLE: " << msg.toString() << endl;
	}
}