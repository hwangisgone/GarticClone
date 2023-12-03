#include <iostream>

#include <arpa/inet.h>		// sockaddr_in

#include "msg/msg_format.hpp"
#include "msg/msg_sendrecv.h"

#include "server_handler.hpp"

using namespace std;

void startGame(const sockaddr_in& clientAddress, ServerHandler * serverHandler) {
	if (compareSockAddrIn(serverHandler->host, clientAddress)) {
		cout << "Game started!" << endl;
		serverHandler->setState(new InGameState());
	}
}

void handleConnect(const sockaddr_in& clientAddress, ServerHandler * serverHandler) {
	cout << "Connection from " << formatSockAddrIn(clientAddress) << ": " << endl;

	Player newPlayer;
	newPlayer.score = 0;

	// If exist, will skip
	auto result = serverHandler->playerMap.emplace(clientAddress, newPlayer);
	if (result.second) {
		cout << "Joined successful!" << endl;

		if (serverHandler->playerMap.size() == 1) { // Make host
			serverHandler->host = clientAddress;
		}
	} else {
		cout << "Joined failed. Player  already exists." << endl;
	}
}

void handleDisconnect(const sockaddr_in& clientAddress, ServerHandler * serverHandler) {
	cout << "Disconnection from " << formatSockAddrIn(clientAddress) << ": " << endl;
	
	// If exist, will skip
	auto result = serverHandler->playerMap.erase(clientAddress);
	// Check if the removal was successful
	if (result == 1) {
		cout << "Remove player successful!" << endl;

		if (serverHandler->playerMap.size() == 0) { // No one left
			cout << "Room will be destroyed!" << endl;

			serverHandler->setState(new DestroyState());
		}
	} else {
		cout << "Remove player failed. Player not found." << endl;
	}
}

void RoomState::handle() {
	// TODO: May consider moving this to somewhere defined once
	sockaddr_in clientAddress{};
	socklen_t clientAddrLen = sizeof(clientAddress);

	cout << "ROOM RUNNING" << endl;
//	int socket, struct sockaddr * targetAddr, socklen_t * targetAddrLen, AppMsg * msg

		// - wait for client to connect
		unique_ptr<BaseMsg> msg = recvMsg(serverHandler->sockfd, (struct sockaddr*)&clientAddress, &clientAddrLen);

		if (!msg) {	// nullptr
			cerr << "SERVER ROOM: Error receiving data" << endl;
			return;
		}
		// - wait for host to start
		switch (msg->type()) {
			case MsgType::CONNECT: 
				handleConnect(clientAddress, serverHandler);
				break;
			case MsgType::DISCONNECT:
				handleDisconnect(clientAddress, serverHandler);
				break;
			default:
				cerr << "SERVER ROOM: MSG TYPE NOT INFERABLE: " << msg->toString() << endl;
		}

}