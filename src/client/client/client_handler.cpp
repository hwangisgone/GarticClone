#include <string>
#include <thread>
#include <memory>

#include <arpa/inet.h>

#include "client_handler.hpp"

#include <msg/msg_sendrecv.h>
#include <printdebug/debugging.h>


using namespace std;

int ClientHandler::sockfd;
sockaddr_in ClientHandler::serverAddress;

void ClientHandler::clientSendMsg(BaseMsg& msg) {
	sendMsg(ClientHandler::sockfd, (struct sockaddr *)&ClientHandler::serverAddress, sizeof(ClientHandler::serverAddress), msg);
}

// recvThread related
void ClientHandler::run() {
	unique_ptr<BaseMsg> msg;
	int timeout_counter = 0;
		
	while (keepAlive) {
		msg = recvMsg(ClientHandler::sockfd, nullptr, nullptr);
		if (!msg) {	// nullptr
			if (errno && EAGAIN || errno && EWOULDBLOCK) {
				DEBUG_COUT("\033[s\r\t\t\t\t\tCLIENT RECV TIMEOUT (" + to_string(timeout_counter) + ")\033[u");	// Save cursor and return
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
int (*getInput)() = nullptr;

void ClientHandler::sendInput() {
	if (getInput == nullptr) {
		DEBUG_PRINT("Cannot send input: getInput function not defined!!!");
		return;
	}
	while (keepAlive) {
		if (getInput() == -1) { 
			DEBUG_PRINT("Input thread ended by user.");
			this->kill();
		}
	}
}

std::thread inputThread;
void ClientHandler::initialize_input_thread(int (*func)()) {
	getInput = func;
	inputThread = std::thread(&ClientHandler::sendInput, this);
}

void ClientHandler::join_input_thread() {
	DEBUG_PRINT("Joining input thread");
	inputThread.join();
}




// Initializations
ClientHandler::ClientHandler(int in_sockfd, sockaddr_in inputAddress) {	// Constructor
	ClientHandler::sockfd = in_sockfd;
	ClientHandler::serverAddress = inputAddress;

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
		strncpy(newPlayerPtr->name, inputName, 50);
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