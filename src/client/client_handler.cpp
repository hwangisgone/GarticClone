#include <string>
#include <thread>
#include <memory>

#include <arpa/inet.h>

#include "client_handler.hpp"

#include "states/new/client_auth.hpp"
#include "msg/msg_sendrecv.h"
#include "debugging.h"


using namespace std;

// recvThread related
void ClientHandler::run() {
	unique_ptr<BaseMsg> msg;
	int timeout_counter = 0;
		
	while (keepAlive) {
		msg = recvMsg(sockfd, nullptr, nullptr);
		if (!msg) {	// nullptr
			if (errno && EAGAIN || errno && EWOULDBLOCK) {
				DEBUG_COUT("CLIENT RECV TIMEOUT (" + to_string(timeout_counter) + ")\033[1A");
				timeout_counter++;
				continue;
			} else {
				DEBUG_PRINT("CLIENT: Error receiving data.");
				return;	
			}
		}
		currentState->handleRecv(*msg);	// This might kill the thread
	}

	DEBUG_PRINT("Finish???");
}

void ClientHandler::kill() {
	keepAlive = false;
}

// FOR TESTING INPUT
// For testing,

void ClientHandler::sendInput() {
	if (getInput == nullptr) {
		DEBUG_PRINT("Cannot send input: getInput function not defined!!!");
		return;
	}
	while (keepAlive) {
		unique_ptr<BaseMsg> msg = this->getInput();
		if (msg != nullptr) { 
			sendMsg(this->sockfd, (struct sockaddr *)&this->serverAddress, sizeof(this->serverAddress), *msg);
		} else {
			DEBUG_PRINT("input: msg is null");
			this->kill();
		}
	}
}

std::thread inputThread;
void ClientHandler::initialize_input_thread(std::unique_ptr<BaseMsg> (*func)()) {
	this->getInput = func;
	inputThread = std::thread(&ClientHandler::sendInput, this);
}

void ClientHandler::join_input_thread() {
	inputThread.join();
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
	std::string playerName(inputName);

	DisplayPlayer newPlayer;

	// If exist, will skip
	auto result = playerMap.emplace(playerID, newPlayer);
	if (result.second) {
		DEBUG_PRINT("(Client) " + playerName + " joined successful!");

		DisplayPlayer * newPlayerPtr = &result.first->second;
		newPlayerPtr->currentScore = 0;
		strcpy(newPlayerPtr->name, inputName);
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