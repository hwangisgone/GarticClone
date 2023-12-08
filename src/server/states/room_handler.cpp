#include "room_handler.hpp"

#include <iostream>
#include "debugging.h"

// roomThread related
void RoomHandler::threadRun() {	// This thing runs at separate thread?
	aliveThread = true;

	MsgWrapper currentMsg;
	while (aliveThread) {
		currentMsg = msgQueue.pop();
		if (!currentMsg.msg) { continue; }

		currentState->handle(*currentMsg.msg, currentMsg.playerID);	// This might kill the thread
	}
}

void RoomHandler::threadKill() {
	aliveThread = false;
	MsgWrapper emptyMsg;
	msgQueue.push(emptyMsg);	// Final message if the queue is empty (stuck on pop())
	DEBUG_PRINT("(Room) Killing...");
}

bool RoomHandler::isDead() {
	return !aliveThread;
}


// Initializations
RoomHandler::RoomHandler(int sockfd) {	// Constructor
	this->sockfd = sockfd;
	this->setState(new RoomState());	// Allocate new state
	roomThread = std::thread(&RoomHandler::threadRun, this);
	DEBUG_PRINT("(Room) created successfully.");
}

RoomHandler::~RoomHandler() {			// Destructor
	threadKill();						// End the thread
	
	roomThread.join();					// Wait for thread to finish before releasing the currentState 💀
	delete currentState;				// Release state resources
	DEBUG_PRINT("(Room) destroyed successfully.");
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


// playerMap
void RoomHandler::addPlayer(int playerID, const sockaddr_in& addr) {
	Player newPlayer;
	newPlayer.currentScore = 0;
	newPlayer.currentAddr = addr;

	// If exist, will skip
	auto result = playerMap.emplace(playerID, newPlayer);
	if (result.second) {
		DEBUG_PRINT("(Room) Joined successful!");

		if (playerMap.size() == 1) {
			host = playerID;			// Make host if there's 1 player
		}
	} else {
		DEBUG_PRINT("(Room) Joined failed. Player already exists.");
	}
}

void RoomHandler::removePlayer(int playerID) {
	// If exist, will skip
	auto result = playerMap.erase(playerID);
	// Check if the removal was successful
	if (result == 1) {
		DEBUG_PRINT("(Room) Remove player successful!");

		if (playerMap.size() == 0) {	// No one left
			DEBUG_PRINT("Room will be destroyed!");
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
		DEBUG_PRINT("Room: Remove player failed. Player not found.");
	}
}