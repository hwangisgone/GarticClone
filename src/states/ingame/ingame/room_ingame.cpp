#include <iostream>
#include <cstring>

#include <server/room_handler.hpp>

#include "msg/msg_ingame.hpp"
#include "msg/msg_next_end.hpp"

#include <msg/msg_sendrecv.h>

#include <room/msg/msg_connection.hpp> // Allow other players to enter/exit in game
#include <printdebug/debugging.h>
#include <database/word_list.hpp>

using namespace std;

bool checkAnswer(char *correct_ans, char *ans)
{
	return strcmp(correct_ans, ans) == 0;
}

void handleScore(const ScoreMsg &msg, int playerID, char *correct_ans, RoomHandler *room, vector<Word>&words)
{
	auto i = room->playerMap.find(playerID);
	int score = getPoint(words, correct_ans); // TODO: fix compiler with this getPoint(correct_ans);

	if (i != room->playerMap.end())
	{
		Player targetPlayer = i->second;
		targetPlayer.currentScore += score;
	}
}


void handleAnswer(const AnswerMsg &msg, int playerID, char *correct_ans, RoomHandler *room, vector<Word>& words)
{
	// get answer from playerID from msg
	// how to get boardcast function of roomhandle here

	AnswerMsg answerMsg = msg;
	room->broadcastExcept(answerMsg, playerID);

	char answer_client[900];
	strcpy(answer_client, msg.answer);

	if (checkAnswer(correct_ans, answer_client))
	{
		ScoreMsg scoreMsg;
		scoreMsg.playerID = playerID;
		scoreMsg.score = getPoint(words, correct_ans);
		handleScore(static_cast<const ScoreMsg &>(scoreMsg), playerID, correct_ans, room, words);
		updateWord(wordsGlobal, correct_ans, true);

		// maybe can boardcast to all that some one correct
		room->broadcastExcept(scoreMsg, playerID);
		
	}
	else
	{
		// something happen ??
	}
}

char* ansStartGame( string wordChoose)
{
	// msg -> answer
	// strcmp(answer, answer);
	// change Word;
	// maybe get word from the queue

	char* output = new char[wordChoose.size() + 1];
    std::strcpy(output, wordChoose.c_str());
    return output;

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
		// startGame(static_cast<const StartMsg &>(msg), wordChoose, answer);
		answer = ansStartGame(wordChoose);
		break;
	case MsgType::ANSWER:
		handleAnswer(static_cast<const AnswerMsg &>(msg), playerID, answer, room, wordsGlobal);
		break;
	case MsgType::SCORE:
		handleScore(static_cast<const ScoreMsg &>(msg), playerID, answer, room, wordsGlobal);
		break;
	case MsgType::NEXT_ROUND:
		// next_round with word choose from word collectionstartGame
		Word w_next = getRandomAndRemove(room->wordCollection);
		answer = ansStartGame(w_next.word);
		break;
	default:
		cerr << "SERVER ROOM: MSG TYPE NOT INFERABLE: " << msg.toString() << endl;
	}
}