#include <iostream>
#include <cstring>

#include "server/room_handler.hpp"

#include "sockaddr_in/sockaddr_in_functions.h"
#include "msg/msg_sendrecv.h"
#include "states/room/msg_connection.hpp"	// Allow other players to enter/exit in game
#include "msg_ingame.hpp"
#include "msg_next_end.hpp"
#include "debugging.h"


using namespace std;

bool checkAnswer(char *correct_ans, char *ans)
{
	return strcmp(correct_ans, ans) == 0;
}

void boardcast(const BaseMsg &msg, int playerID, RoomHandler *room){

	auto find_addr = room->playerMap.find(playerID);
	sockaddr_in send_addr = find_addr->second.currentAddr;

	for (auto& pair : room->playerMap) {
        Player& player = pair.second;
		sockaddr_in to_boardcast_addr = player.currentAddr;
		if(!compareSockAddrIn(send_addr, to_boardcast_addr)){
			// send_msg
		}
	}
}

int add_score(char *correct_ans)
{
	int score;
	// check correct_answer in what level ( easy, middile, hard ) to add score
	return score;
}

void handleScore(const ScoreMsg &msg, int playerID, char* correct_ans, RoomHandler *room)
{
	auto i = room->playerMap.find(playerID);
	int score = add_score(correct_ans);
	if (i != room->playerMap.end())
	{
		Player targetPlayer = i->second;
		targetPlayer.currentScore += score;
	}
}

void handleAnswer(const BaseMsg &msg, int playerID, char *correct_ans, RoomHandler *room)
{
	char *answer;

	boardcast(msg, playerID, room);

	if (checkAnswer(correct_ans, answer))
		{
			handleScore(static_cast<const ScoreMsg &>(msg), playerID, correct_ans, room);
			// maybe can boardcast to all that some one correct
		}
	else
	{
		//
	}
}

void InGameState::handle(const BaseMsg &msg, int playerID)
{
	DEBUG_PRINT("  (InGameState) " + msg.toString());

	unordered_map<int, Player> state_playerMap;
	state_playerMap = room->playerMap;
	auto index = state_playerMap.find(playerID);

	switch (msg.type())
	{
	case MsgType::ANSWER:
		handleAnswer(static_cast<const AnswerMsg &>(msg), playerID, answer, room);
		break;
	case MsgType::SCORE:
		handleScore(static_cast<const ScoreMsg &>(msg), playerID, answer, room);
		break;
	default:
		cerr << "SERVER ROOM: MSG TYPE NOT INFERABLE: " << msg.toString() << endl;
	}
}