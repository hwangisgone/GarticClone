#include <cstring>

#include "room_handler.hpp"

#include <database/word_list.hpp>
#include <database/textdatabase.hpp>

#include <msg/msg_sendrecv.h>
#include <printdebug/debugging.h>

// roomThread related
void RoomHandler::threadRun() {	// This thing runs at separate thread?
	aliveThread = true;

	MsgWrapper currentMsg;
	while (aliveThread || msgQueue.size() > 0) {
		currentMsg = msgQueue.pop();
		if (!currentMsg.msg) {
			DEBUG_PRINT("(Room) nullptr msg from threadKill(). Thread is killed.");
			break; 
		}

		currentState->handle(*currentMsg.msg, currentMsg.playerID);	// This might kill the thread
	}
}

void RoomHandler::threadKill() {
	if (aliveThread) {
		aliveThread = false;
		MsgWrapper emptyMsg;
		msgQueue.push(emptyMsg);	// Final message if the queue is empty (stuck on pop())
		DEBUG_PRINT("(Room) Killing thread...");
	}
}

bool RoomHandler::isDead() {
	return !aliveThread;
}


// Initializations
RoomHandler::RoomHandler(int sockfd) {	// Constructor
	this->sockfd = sockfd;
	this->setState(new RoomState());	// Allocate new state
	roomThread = std::thread(&RoomHandler::threadRun, this);
	DEBUG_PRINT("{Room} created successfully.");
}

RoomHandler::~RoomHandler() {			// Destructor
	threadKill();						// End the thread
	
	roomThread.join();					// Wait for thread to finish before releasing the currentState 💀
	delete currentState;				// Release state resources
	DEBUG_PRINT("{Room} destroyed successfully.");
}

void RoomHandler::setState(ServerState* newState) {
	if (newState == nullptr) {
		DEBUG_PRINT("setState cannot be nullptr.");
		return;
	}

	if (currentState != nullptr) {
		delete currentState;
	}

	currentState = newState;
	currentState->setHandler(this);	// Backref
}

// broadcasting
void RoomHandler::broadcast(BaseMsg& msg) const {
	for (const auto& pair : playerMap) {
		sendMsg(this->sockfd, (struct sockaddr*)&pair.second.currentAddr, sizeof(pair.second.currentAddr), msg);
	}
}
void RoomHandler::broadcastExcept(BaseMsg& msg, int playerID) const {
	for (const auto& pair : playerMap) {
		if (pair.first != playerID) {
			sendMsg(this->sockfd, (struct sockaddr*)&pair.second.currentAddr, sizeof(pair.second.currentAddr), msg);
		}
	}
}

// playerMap
void RoomHandler::addPlayer(int playerID, const sockaddr_in& addr, const PlayerAccount& account) {
	std::string playerName(account.playerName);

	Player newPlayer(addr, account);


	// If exist, will skip
	auto result = playerMap.emplace(playerID, newPlayer);
	if (result.second) {
		TEST_PRINT("(Room) '" + playerName + "' joined successful!");
		
		Player * newPlayerPtr = &result.first->second;
		newPlayerPtr->currentScore = 0;

		if (playerMap.size() == 1) {
			host = playerID;			// Make host if there's 1 player
		}
	} else {
		TEST_PRINT("(Room) Joined failed. " + playerName + " already exists.");
	}
}

void RoomHandler::removePlayer(int playerID) {
	std::string playerName = "Player " + std::to_string(playerID);
	// If exist, will skip
	auto result = playerMap.erase(playerID);
	// Check if the removal was successful
	if (result == 1) {
		DEBUG_PRINT("(Room) Remove " + playerName + " successful!");

		if (playerMap.size() == 0) {	// No one left
			DEBUG_PRINT("(Room) Removed last player so room will be destroyed! Triggering threadKill().");
			threadKill();
			return;
		}

		// TODO: player list? may not be the same. Need some way to determine it
		if (playerID == host) {			// If host disconnect then person with highest score get to be the host
			int highest_score = 0;
			int highest_playerID = playerMap.begin()->first;
			for (const auto& pair : playerMap) {
				if (pair.second.currentScore > highest_score) {
					highest_playerID = pair.first;
					highest_score = pair.second.currentScore;
				}
			}
			host = highest_playerID;
		}
	} else {
		DEBUG_PRINT("(Room) Remove " + playerName + " failed. Player not found.");
	}
}


void RoomHandler::setModeAutoRound() {
	this->gameMode = 0;
	this->roundLeft = playerMap.size();
}

void RoomHandler::setModeRounds(int rounds) {
	this->gameMode = 0;
	this->roundLeft = rounds;
}

void RoomHandler::setModeScoring(int score) {
	this->gameMode = 1;
	this->targetScore = score;
}

bool RoomHandler::endGameCheck() {
	if (this->gameMode == 0) {			// Round mode. Ends after predetermined rounds
		if (this->roundLeft <= 0) {
			DEBUG_PRINT("Game (rounds) ended.");
			return true;
		} else {
			this->roundLeft--;
			DEBUG_PRINT("Round left: " + std::to_string(this->roundLeft));
		}
	} else if (this->gameMode == 1) {	// Scoring mode. Ends after any player reaches certain point
		for (const auto& pair : playerMap) {
			if (pair.second.currentScore > this->targetScore) {
				DEBUG_PRINT("Game (score) ended.");
				return true;		// Leaderboard will handle the ranking
			}
		}
	} else {
		DEBUG_PRINT("Game mode not available?");
	}

	return false;
}