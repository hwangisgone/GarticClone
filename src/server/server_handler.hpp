#ifndef SERVER_HANDLER_H
#define SERVER_HANDLER_H

#include <unordered_map>
#include <sys/socket.h>
#include "sockaddr_in/sockaddr_in_functions.h"

class ServerHandler;

// State interface
class ServerState {
protected:
	ServerHandler * serverHandler;	// This backreference can be used by States to transition the * ServerHandler to another State.
public:
	virtual void handle() = 0;

	void setHandler(ServerHandler * handler) {
		serverHandler = handler;
	}
};

// Concrete States
class LobbyState: public ServerState {
public:
	void handle() override;
};

class RoomState: public ServerState {
private:
	bool init = false;
public:
	void handle() override;
};

class InGameState: public ServerState {
public:
	void handle() override;
};

class LeaderboardState: public ServerState {
public:
	void handle() override;
};

class DestroyState: public ServerState {
public:
	void handle() override;
};

// enum GameState {
// 	LOBBY,
// 	ROOM,
// 	INGAME,
// 	LEADERBOARD,
// 	ENDSERVER,
// };

struct Player {
	int score;
};

// Context
class ServerHandler {
private:
	ServerState* currentState = nullptr;
	bool keepAlive = true;

public:
	int sockfd;
	sockaddr_in host;
	std::unordered_map<sockaddr_in, Player, sockaddr_in_hash, sockaddr_in_equal> playerMap;

	ServerHandler(int sockfd) {
		this->sockfd = sockfd;
		this->setState(new RoomState());
	}	// Constructor

	void setState(ServerState* newState) {
		if (currentState != nullptr) {
			delete currentState;
		}

		currentState = newState;
		currentState->setHandler(this);	// Backref
	}


	void run();
	void kill();
};

#endif