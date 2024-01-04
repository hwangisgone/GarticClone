#include <iostream>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <unistd.h> // Unix for closing

#include "server_init.hpp"	// All server handles

#include <database/textdatabase.hpp>
#include <printdebug/debugging.h>

/*
* Create a new server
* [IN] port: what port to use
* [OUT] sockfd: socket file descriptors
*/
int initialize_server(int port) {
	// 1. Create UDP socket
	int serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if (serverSocket == -1) {
		std::cerr << "Error in socket()" << std::endl;
		return -1;	// exit(1);
	}

	// 2. Bind the socket to a specific address and port
	sockaddr_in serverAddress{};
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY); //??	/* INADDR_ANY puts your IP address automatically */
	serverAddress.sin_port = htons(port);

	if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
		std::cerr << "Error binding socket" << std::endl;
		close(serverSocket);
		return -1;
	}

	printf("Server is listening on port %d\n", port);
	return serverSocket;
}


void cleanup_server(int sockfd) {

	close(sockfd);
}

void run_server(int sockfd) {
	ServerLobby server1(sockfd);
	server1.run();
}

std::unique_ptr<ServerLobby> get_server(int sockfd) {
	return std::make_unique<ServerLobby>(sockfd);
}
/*
void handleState() {
	STATE_LOBBY => doesn't have one

	STATE_ROOM => CONNECT | DISCONNECT | START 				*** handleRoom()
	STATE_GAME => DRAW | ANSWER | POINT | NEXT_ROUND | END	*** handleGame()
	STATE_LEADERBOARD => LOBBY 								*** handleLeaderboard()
}
*/











