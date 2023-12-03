#include <iostream>

#include <arpa/inet.h>		// sockaddr_in

#include "msg/msg_format.hpp"
#include "msg/msg_sendrecv.h"

#include "game_format.h"

#include "server_handle.h"

using namespace std;

extern RoomInfo currentRoom;	// Definition in server.cpp

void startGame(const sockaddr_in& clientAddress) {
	if (compareSockAddrIn(currentRoom.host, clientAddress)) {
		cout << "Game started!" << endl;
		currentRoom.currentState = GameState::INGAME;
	}
}

void handleConnect(const sockaddr_in& clientAddress) {
	cout << "Connection from " << formatSockAddrIn(clientAddress) << ": " << endl;

	Player newPlayer;
	newPlayer.score = 0;

	// If exist, will skip
	auto result = currentRoom.playerMap.emplace(clientAddress, newPlayer);
	if (result.second) {
		cout << "Joined successful!" << endl;

		if (currentRoom.playerMap.size() == 1) { // Make host
			currentRoom.host = clientAddress;
		}
	} else {
		cout << "Joined failed. Player  already exists." << endl;
	}
}

void handleDisconnect(const sockaddr_in& clientAddress) {
	cout << "Disconnection from " << formatSockAddrIn(clientAddress) << ": " << endl;
	
	// If exist, will skip
	auto result = currentRoom.playerMap.erase(clientAddress);
	// Check if the removal was successful
	if (result == 1) {
		cout << "Remove player successful!" << endl;

		if (currentRoom.playerMap.size() == 0) { // No one left
			cout << "Room will be destroyed!" << endl;
			currentRoom.currentState = GameState::ENDSERVER;
		}
	} else {
		cout << "Remove player failed. Player not found." << endl;
	}
}


void handleRoom(int sockfd) {
	sockaddr_in clientAddress{};
	socklen_t clientAddrLen = sizeof(clientAddress);

//	int socket, struct sockaddr * targetAddr, socklen_t * targetAddrLen, AppMsg * msg
	while (currentRoom.currentState == GameState::ROOM) {
		// - wait for client to connect
		unique_ptr<BaseMsg> msg = recvMsg(sockfd, (struct sockaddr*)&clientAddress, &clientAddrLen);

		if (!msg) {	// nullptr
			cerr << "SERVER ROOM: Error receiving data" << endl;
			continue;
		}
		// - wait for host to start
		switch (msg->type()) {
			case MsgType::CONNECT: 
				handleConnect(clientAddress);
				break;
			case MsgType::DISCONNECT:
				handleDisconnect(clientAddress);
				break;
			default:
				cerr << "SERVER ROOM: MSG TYPE NOT INFERABLE: " << msg->toString() << endl;
		}
	}
}