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

	std::thread t;
	int roundIndex ;

public:
	InGameState(RoomHandler *handler, int index); // Initializer

	void handle(const BaseMsg &msg, int playerID) override;

	void countTime()
	{
		int k = 60; // 1 minutes
		for (int i = k; i > 0; --i)
		{
			// cout << "\rTime remaining: " << i << flush;
			this_thread::sleep_for(std::chrono::seconds(1));
		}
	}
	void handleCountTime(RoomHandler *handler);
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

// Timer thread
// static TSQueue<MsgWrapper> msgQueue;
// static addtoQueue(5) {
// 		msgQueue.push(currentTime + 5, func)
// }


// Room thread -> static addtoQueue(5, func)


// Timer Thread 1s ->
// while (end 1s) 
//	-> find msgQueue(0) -> func
//	-> msgQueue.pop
//  -> 
// } 


// Client -> Server
// Client send -> Server Lobby



// Context
class RoomHandler
{
private:
	ServerState *currentState = nullptr;

	std::thread roomThread;
	std::atomic<bool> aliveThread; // atomic for safety?	// TODO: May not be needed
public:
	TSQueue<MsgWrapper> msgQueue; // Exchanging data between threads

	int sockfd;
	int host; // playerID
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

	WordHandler handlerWord;
};

#endif
