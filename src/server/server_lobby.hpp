#ifndef SERVER_LOBBY_H
#define SERVER_LOBBY_H

#include "sockaddr_in/sockaddr_in_functions.h"
#include "room_handler.hpp"
#include <string>

struct PlayerAccount {
	int playerID;
	int multiGameScore;
	std::string name;
};

struct PlayerSession {
	PlayerAccount * account = nullptr;
	RoomHandler * inRoom = nullptr;
};

class ServerLobby {
private:
	std::atomic<bool> keepAlive = true;
	int sockfd;

	std::unordered_map<sockaddr_in, PlayerSession, sockaddr_in_hash, sockaddr_in_equal> sessionRoomMap;
	int accountCount = 0;
	std::vector<PlayerAccount> allAccounts;
	std::vector<RoomHandler *> allRooms;
public:
	ServerLobby(int server_sock) {
		sockfd = server_sock;
	}

	void addSession(const sockaddr_in& addr);
	void removeSession(const sockaddr_in& addr);

	void run();
	void kill();
};

#endif