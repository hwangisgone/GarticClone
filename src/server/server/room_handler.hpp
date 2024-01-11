#ifndef ROOM_HANDLER_H
#define ROOM_HANDLER_H

#include <unordered_map>
#include <thread>
#include <atomic>
#include <cstring>

#include <arpa/inet.h>

#include <utils/safe_queue.hpp>

#include <database/textdatabase.hpp>
#include <database/word_list.hpp>

#include <msg/msg_format.hpp>

class RoomHandler;

// State interface
class ServerState
{
protected:
	RoomHandler *room; // This backreference can be used by States to transition the * RoomHandler to another State.

public:
	virtual void handle(const BaseMsg &msg, int playerID) = 0;

	void setHandler(RoomHandler *handler)
	{
		room = handler;
	}
};

// Concrete States

class RoomState : public ServerState
{
private:
	// bool init = false;
public:
	void handle(const BaseMsg &msg, int playerID) override;
};

class InGameState : public ServerState
{
private:
	int answerIndex; // Must somehow point to original word
	int drawerID;
	Word roundAnswer;
	int correctCount = 0;

	// std::thread t;

public:
	InGameState(RoomHandler *handler); // Initializer

	void handle(const BaseMsg &msg, int playerID) override;
};

class LeaderboardState : public ServerState
{
public:
	void handle(const BaseMsg &msg, int playerID) override;
};

// GameState {
// 	LOBBY,
// 	ROOM,
// 	INGAME,
// 	LEADERBOARD,
// 	ENDSERVER,
// };

struct Player
{
	const PlayerAccount &account;
	const sockaddr_in currentAddr;
	int currentScore;
	Player(const sockaddr_in &in_addr, const PlayerAccount &in_acc) : currentAddr(in_addr), account(in_acc) {}
};




// Context
class RoomHandler
{
private:
	ServerState *currentState = nullptr;

	std::thread roomThread;
	std::atomic<bool> aliveThread; // atomic for safety?

	// For endGameCheck
	int gameMode = 0;
	int roundLeft = 0;
	int targetScore = 0;
public:
	TSQueue<MsgWrapper> msgQueue; // Exchanging data between threads

	int sockfd;
	int host; // playerID

	int roomID;
	char roomName[50];
	
	std::unordered_map<int, Player> playerMap; // Map (playerID, Player)

	RoomHandler(int sockfd);
	~RoomHandler();

	void setState(ServerState *newState);

	bool isDead();
	void threadRun();
	void threadKill();

	void addPlayer(int playerID, const sockaddr_in &addr, const PlayerAccount &account);
	void removePlayer(int playerID);

	void broadcast(BaseMsg &msg) const; // Cannot use const for BaseMsg because sendMsg needs to calculate msgLength
	void broadcastExcept(BaseMsg &msg, int playerID) const;

	// In Game stuffs
	WordHandler handlerWord;
	int roundTimer = 25;	// Default 25 seconds
	void setModeAutoRound();
	void setModeRounds(int rounds);
	void setModeScoring(int score);
	bool endGameCheck();
};

#endif
