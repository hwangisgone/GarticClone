#ifndef SERVER_LOBBY_H
#define SERVER_LOBBY_H

#include <string>

#include "room_handler.hpp"

#include <sockaddr_in/sockaddr_in_functions.hpp>

#include <lobby/msg/msg_lobby.hpp>
#include <database/textdatabase.hpp>

struct PlayerSession {
	const PlayerAccount& account;
	const sockaddr_in& addr;
	RoomHandler * inRoom = nullptr;
	PlayerSession(const sockaddr_in& in_addr, const PlayerAccount& in_acc) : addr(in_addr), account(in_acc) {}
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

	void addSession(const sockaddr_in& addr, const PlayerAccount& account);
	void removeSession(const sockaddr_in& addr);
public:
	ServerLobby(int server_sock) {
		sockfd = server_sock;
	}

	void run();
	void kill();
};

#endif