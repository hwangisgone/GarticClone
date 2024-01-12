#include <iostream>
#include <cstring>
#include <random>
#include <vector>
#include <server/room_handler.hpp>

#include "msg/msg_ingame.hpp"
#include "msg/msg_next_end.hpp"

#include <msg/msg_sendrecv.h>

#include <room/room_connection.hpp> // Allow other players to enter/exit in game
#include <database/word_list.hpp>	// Word handling

#include <utils/rng.hpp>			// Choosing who to draw
#include <timer/timer_thread.hpp>	// End round

#include <printdebug/debugging.h>

using namespace std;

InGameState::InGameState(RoomHandler *room)
{							// Initialize a new game
	this->setHandler(room); // Required, otherwise segmentation fault

	this->roundAnswer = room->handlerWord.getRandomAndRemove();

	// Get random playerID from the map
	std::uniform_int_distribution<size_t> dist(0, room->playerMap.size() - 1);
	size_t randomIndex = dist(gameRng); // Iterate to the random index to get the corresponding key
	auto it = std::next(room->playerMap.begin(), randomIndex);

	DEBUG_PRINT("New round started. This round word: '" + string(this->roundAnswer.word) + "'");
	this->drawerID = it->first;
	// Get random playerID from the map
	// Choose as player to draw

	NextRoundMsg nextmsg;
	nextmsg.timer = room->roundTimer;
	nextmsg.role = 0;
	room->broadcastExcept(nextmsg, this->drawerID);

	// Send role to drawer
	nextmsg.role = 1;
	strncpy(nextmsg.word, this->roundAnswer.word, sizeof(this->roundAnswer.word));
	Player drawerPlayer = room->playerMap.at(drawerID);
	sendMsg(room->sockfd, (struct sockaddr *)&drawerPlayer.currentAddr, sizeof(drawerPlayer.currentAddr), nextmsg);

	// TODO: gamesettings with timer here
	TimerThread::addTimer(25, room->roomID, 1);
}


bool handleAnswer(const AnswerMsg &msg, int playerID, const Word &correct_ans, RoomHandler *room)
{
	bool isCorrect = false;

	if (correct_ans.isTheSame(msg.answer))
	{
		try {
			// Add score and send score message
			Player &ppp = room->playerMap.at(playerID);
			ppp.currentScore += correct_ans.getWordPoint();

			ScoreMsg msg;
			msg.playerID = playerID;
			msg.score = ppp.currentScore;
			room->broadcast(msg);

			isCorrect = true;
		}
		catch (const std::out_of_range &e) {
			cerr << "PLAYER " << playerID << " NOT FOUND (handleScore). Exception at " << e.what() << endl;
		}
	}
	else
	{
		// Only broadcast incorrect asnwers
		AnswerMsg answermsg = msg;
		answermsg.playerID = playerID;
		room->broadcast(answermsg, playerID);
	}

	return isCorrect;
}

// TODO: Handle if the player answered correctly. (Cannot answer again)
// TODO: TIMER??? -> room->setState(new InGameState(room));
//
// total = playerMap.size()
// correct = this->correctCount		 ("this" is InGameState)
// playerDisconnect (correct) -> correctCount - 1
//
//		- Update at end of round OR update at handleAnswer
//		- No more findWord
// 		WordHandler::updateWord(wordsGlobal, correct_ans, true);
//

void InGameState::handle(const BaseMsg &msg, int playerID)
{
	DEBUG_PRINT("  (InGameState) " + msg.toString());

	switch (msg.type())
	{
	case MsgType::JOIN_ROOM:
	{
		RoomConn::handleConnect(static_cast<const JoinRoomMsg &>(msg), playerID, room);
		break;
	}
	case MsgType::DISCONNECT:
	{
		RoomConn::handleDisconnect(playerID, room);
		if (room->playerMap.size() == 1) {
			TEST_PRINT("(InGame) Game exited because there's only 1 player left");
			TimerThread::removeRoomTimers(room->roomID);
			RoomConn::backToRoom(room);
		}
		break;
	}

	case MsgType::DRAW:
	{
		if (playerID == this->drawerID)
		{
			TEST_PRINT("  (InGameState) Drawing...");
			DrawMsg newmsg = static_cast<const DrawMsg &>(msg);
			room->broadcastExcept(newmsg, playerID);
		}
		else
		{
			TEST_PRINT("  (InGameState) Non-Drawer attempted to draw????");
		}
		break;
	}
	case MsgType::ANSWER:
	{ // Send score here if correct
		if (playerID != this->drawerID)
		{
			if (handleAnswer(static_cast<const AnswerMsg &>(msg), playerID, this->roundAnswer, room))
			{
				this->correctCount += 1;
			}
		}
		else
		{
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