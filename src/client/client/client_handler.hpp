#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

#include <unordered_map>
#include <arpa/inet.h>

#include <msg/msg_format.hpp>

class ClientHandler;

// State interface
class ClientState {
protected:
	ClientHandler * client;	// This backreference can be used by States to transition the * ClientHandler to another State.
public:
	virtual void handleRecv(const BaseMsg& msg) = 0;

	void setHandler(ClientHandler * handler) {
		client = handler;
	}
};

// Concrete States
class AuthState: public ClientState {
private:
	bool loggedIn = false;
public:
	void handleRecv(const BaseMsg& msg) override;
	
	static void requestLogin(char type, const char * name, const char * pass);

	// TODO:
	// static void requestGuest(const char * name);
};

class LobbyState: public ClientState {
public:
	void handleRecv(const BaseMsg& msg) override;

	static void requestGetRooms();
	static void requestCreateRoom(const char * name);
	static void requestJoinRoom(int roomID);
};

class RoomState: public ClientState {
public:
	void handleRecv(const BaseMsg& msg) override;

	static void requestStart();
	static void requestDisconnect();
};

class InGameState: public ClientState {
public:
	void handleRecv(const BaseMsg& msg) override;
	
	static void requestDraw(int x, int y, const char* color, int size, int start);
	static void requestAnswer(const char* answer);
};

class LeaderboardState: public ClientState {
public:
	void handleRecv(const BaseMsg& msg) override;

	static void requestGetLeaderboard();
	static void requestBackToRoom();
};

// GameState {
// 	LOBBY,
// 	ROOM,
// 	INGAME,
// 	LEADERBOARD,
// 	ENDSERVER,
// };

struct DisplayPlayer {
	char name[50];
	int currentScore;
};

// Context
class ClientHandler {
private:
	ClientState* currentState = nullptr;
	bool keepAlive = true;
public:
	static int sockfd;
	static sockaddr_in serverAddress;
	static void clientSendMsg(BaseMsg& msg);

	std::unordered_map<int, DisplayPlayer> playerMap;	// Map (playerID, Player)

	ClientHandler(int sockfd, sockaddr_in inputAddress);
	~ClientHandler();

	void setState(ClientState* newState);

	void run();
	void kill();

	void addPlayer(int playerID, const char * inputName);
	void removePlayer(int playerID);

	void sendInput();
	void initialize_input_thread(int (*func)());
	void join_input_thread();
};

#endif
