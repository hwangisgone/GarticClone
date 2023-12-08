#ifndef SERVER_LOBBY_H
#define SERVER_LOBBY_H

	//  TODO:
	//	structure for each room
	//	each room will implement thread
	//	
	// Need an vector to store Room object
	// The map will reference it

/*


	cout << "ROOM RUNNING" << endl;
//	int socket, struct sockaddr * targetAddr, socklen_t * targetAddrLen, AppMsg * msg


	// TODO: Move this to another thread
	// 2 threads:
	// - recvMsg thread
	// - sendMsg thread(s): thread for handling, each thread is a mini server handling room
	// - Queue to connect both


*/

#include "sockaddr_in/sockaddr_in_functions.h"
#include "states/room_handler.hpp"
#include <string>

struct PlayerAccount {
	int playerID;
	int multiGameScore;
	std::string name;
	std::string password;
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