#ifndef ROOM_HANDLER_H
#define ROOM_HANDLER_H

#include <unordered_map>

#include "safe_queue.hpp"
#include <thread>
#include <atomic>

#include "msg/msg_format.hpp"

class RoomHandler;

// State interface
class ServerState {
protected:
	RoomHandler * room;	// This backreference can be used by States to transition the * RoomHandler to another State.
public:
	virtual void handle(const BaseMsg& msg, int playerID) = 0;

	void setHandler(RoomHandler * handler) {
		room = handler;
	}
};

// Concrete States

class RoomState: public ServerState {
private:
	// bool init = false;
public:
	void handle(const BaseMsg& msg, int playerID) override;
};

class InGameState: public ServerState {
public:
	void handle(const BaseMsg& msg, int playerID) override;
};

class LeaderboardState: public ServerState {
public:
	void handle(const BaseMsg& msg, int playerID) override;
};

// enum GameState {
// 	LOBBY,
// 	ROOM,
// 	INGAME,
// 	LEADERBOARD,
// 	ENDSERVER,
// };

struct Player {
	int currentScore;
	sockaddr_in currentAddr;
};

struct MsgWrapper {
	int playerID;
	std::unique_ptr<BaseMsg> msg;
};

// Context
class RoomHandler {
private:
	int roomID;
	ServerState* currentState = nullptr;

	std::thread roomThread;
	std::atomic<bool> aliveThread;				// atomic for safety?	// TODO: May not be needed
public:
	TSQueue<MsgWrapper> msgQueue;				// Exchanging data between threads
	
	int sockfd;
	int host;	// playerID
	std::unordered_map<int, Player> playerMap;	// Map (playerID, Player)

	RoomHandler(int sockfd);
	~RoomHandler();

	void setState(ServerState* newState);

	bool isDead();
	void threadRun();
	void threadKill();

	void addPlayer(int playerID, const sockaddr_in& addr);
	void removePlayer(int playerID);
	void broadCast();
};

#endif