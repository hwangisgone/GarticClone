#ifndef SERVER_LOBBY_H
#define SERVER_LOBBY_H

#include <string>

#include "sockaddr_in/sockaddr_in_functions.h"
#include "room_handler.hpp"
#include "states/lobby/msg_lobby.hpp"

#include "database/textdatabase.hpp"

struct PlayerSession {
	PlayerAccount * account = nullptr;
	RoomHandler * inRoom = nullptr;
	sockaddr_in addr;
};

class ServerLobby {
private:
	std::atomic<bool> keepAlive = true;
	int sockfd;

	// Map address with PlayerSession
	std::unordered_map<sockaddr_in, PlayerSession, sockaddr_in_hash, sockaddr_in_equal> sessionRoomMap;

	// Map roomID with room
	int roomCount = 0;
	std::unordered_map<int, RoomHandler *> allRooms;

	bool joinRoom(PlayerSession& client, JoinRoomMsg& joinmsg);
	void createRoom(PlayerSession& creator);

	void LobbyHandle(MsgWrapper& wrapper, const sockaddr_in& clientAddress);

	void addSession(const sockaddr_in& addr);
	void removeSession(const sockaddr_in& addr);
public:
	ServerLobby(int server_sock) {
		sockfd = server_sock;
	}

	void run();
	void kill();
};

#endif