#ifndef ROOM_HANDLER_H
#define ROOM_HANDLER_H

#include <unordered_map>

#include "safe_queue.hpp"
#include <arpa/inet.h>
#include <thread>
#include <atomic>
#include <cstring>
#include "msg/msg_format.hpp"
#include "database/textdatabase.hpp"

class RoomHandler;

struct Statistic{
	int totalCount;
	int successCount;
};

// State interface
class ServerState {
protected:
	RoomHandler * room;	// This backreference can be used by States to transition the * RoomHandler to another State.

public:
	std::unordered_map<std::string, Statistic> statisticWord;

	virtual void handle(const BaseMsg& msg, int playerID) = 0;

	void setHandler(RoomHandler * handler) {
		room = handler;
	}

	int percentageWord(char *word){
		std::string wordString(word);
		Statistic st  = statisticWord[wordString];
		return st.successCount*100/st.totalCount;
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
	char *answer;
	void handle(const BaseMsg& msg, int playerID) override;
	
};

class LeaderboardState: public ServerState {
public:
	void handle(const BaseMsg& msg, int playerID) override;
};

// GameState {
// 	LOBBY,
// 	ROOM,
// 	INGAME,
// 	LEADERBOARD,
// 	ENDSERVER,
// };

struct Player {
	PlayerAccount * account;
	int currentScore;
	sockaddr_in currentAddr;
};

// Context
class RoomHandler {
private:
	ServerState* currentState = nullptr;

	std::thread roomThread;
	std::atomic<bool> aliveThread;				// atomic for safety?	// TODO: May not be needed
public:
	TSQueue<MsgWrapper> msgQueue;				// Exchanging data between threads
	
	int sockfd;
	int host;	// playerID
	int modeGame;
	std::unordered_map<int, Player> playerMap;	// Map (playerID, Player)	

	RoomHandler(int sockfd);
	~RoomHandler();

	void setState(ServerState* newState);
	void setMode(int modeGame);
	
	bool isDead();
	void threadRun();
	void threadKill();

	void addPlayer(int playerID, const char * inputName, const sockaddr_in& addr);
	void removePlayer(int playerID);

	void broadcast(BaseMsg& msg) const;	// Cannot use const for BaseMsg because sendMsg needs to calculate msgLength
	void broadcastExcept(BaseMsg& msg, int playerID) const;
};

#endif
