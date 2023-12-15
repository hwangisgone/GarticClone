#include <string>
#include "msg/msg_sendrecv.h"
#include "debugging.h"

#include "client_handler.hpp"
#include "states/new/client_auth.hpp"

using namespace std;

// recvThread related
void ClientHandler::run() {
	unique_ptr<BaseMsg> msg;
		
	while (keepAlive) {
		msg = recvMsg(sockfd, nullptr, nullptr);
		if (!msg) {	// nullptr
			cerr << "CLIENT: Error receiving data" << endl;
			return;
		}
		currentState->handleRecv(*msg);	// This might kill the thread
	}

	DEBUG_PRINT("Finish???");
}

void ClientHandler::kill() {
	keepAlive = false;
}



// Initializations
ClientHandler::ClientHandler(int sockfd, sockaddr_in inputAddress) {	// Constructor
	this->sockfd = sockfd;
	this->serverAddress = inputAddress;

	DEBUG_PRINT("{ClientHandler} created successfully.");
	this->setState(new AuthState());	// Allocate new state
}

ClientHandler::~ClientHandler() {		// Destructor
	delete currentState;				// Release state resources
	DEBUG_PRINT("{ClientHandler} destroyed successfully.");
}

void ClientHandler::setState(ClientState* newState) {
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
void ClientHandler::addPlayer(int playerID, const char * inputName) {
	std::string playerName = "Player " + std::to_string(playerID);

	DisplayPlayer newPlayer;
	strcpy(newPlayer.name, inputName);
	newPlayer.currentScore = 0;

	// If exist, will skip
	auto result = playerMap.emplace(playerID, newPlayer);
	if (result.second) {
		DEBUG_PRINT("(Client) " + playerName + " joined successful!");
	} else {
		DEBUG_PRINT("(Client) Joined failed. " + playerName + " already exists.");
	}
}

void ClientHandler::removePlayer(int playerID) {
	std::string playerName = "Player " + std::to_string(playerID);

	auto result = playerMap.erase(playerID);
	if (result == 1) {
		DEBUG_PRINT("(Client) Remove " + playerName + " successful!");
	} else {
		DEBUG_PRINT("(Client) Remove " + playerName + " failed. Player not found.");
	}
}