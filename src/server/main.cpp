#include <iostream>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <unistd.h> // Unix for closing

#include "game_format.h"
#include "server_handle.h"	// All server handles

#include "network_const.h"

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
	serverAddress.sin_addr.s_addr = INADDR_ANY;	// htonl(INADDR_ANY)??	/* INADDR_ANY puts your IP address automatically */
	serverAddress.sin_port = htons(port);

	if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
		std::cerr << "Error binding socket" << std::endl;
		close(serverSocket);
		return -1;
	}

	std::cout << "Server is listening on port " << port << std::endl;
	return serverSocket;
}


void cleanup_server(int sockfd) {
	close(sockfd);
}


// Global state
RoomInfo currentRoom;

void run_server(int sockfd) {
	while(true) {
		switch(currentRoom.currentState) {
			// No LOBBY case
			case GameState::ROOM:
				handleRoom(sockfd);
				break;
			case GameState::INGAME:
				break;
			case GameState::LEADERBOARD:
				break;
			case GameState::ENDSERVER:
				return;
				break;
			default:
				std::cerr << "RUN SERVER: STATE UNKNOWN??? " << std::endl;
		}
	}
}
/*
void handleState() {
	STATE_LOBBY => doesn't have one

	STATE_ROOM => CONNECT | DISCONNECT | START 				*** handleRoom()
	STATE_GAME => DRAW | ANSWER | POINT | NEXT_ROUND | END	*** handleGame()
	STATE_LEADERBOARD => LOBBY 								*** handleLeaderboard()
}
*/

/*
serverInfo {
	host: pointer
	current_state: STATE_ENUM
	playerlist (including host) [
		playerA: {
			addr:
			score:
		} 
	]
} */

int main(){
	int server_sock; /* file descriptors */

	server_sock = initialize_server(CHOSEN_PORT);

	currentRoom.currentState = GameState::ROOM; // Testing
	run_server(server_sock);
	cleanup_server(server_sock);
	
	return 0;
}











