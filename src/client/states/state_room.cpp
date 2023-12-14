#include <iostream>

#include <arpa/inet.h>		// sockaddr_in

#include "msg/types/msg_connect.hpp"
#include "msg/types/msg_transition.hpp"

#include "debugging.h"
#include "client_handler.hpp"


void startGame(const StartMsg& msg, ClientHandler * client) {
	DEBUG_PRINT("  (StateRoom) Game started!!!");
	client->setState(new InGameState());
}

void handleConnect(const ConnectMsg& msg, ClientHandler * client) {
	DEBUG_PRINT("  (StateRoom) Connection from " + std::string(msg.name));
	client->addPlayer(msg.playerID, msg.name);
}

void handleDisconnect(const DisconnectMsg& msg, ClientHandler * client) {
	DEBUG_PRINT("  (StateRoom) Disconnection.");
	client->removePlayer(msg.playerID);
}

void RoomState::handleRecv(const BaseMsg& msg) {
	// - wait for host to start
	DEBUG_PRINT("  (StateRoom) " + msg.toString());

	switch (msg.type()) {
		case MsgType::CONNECT: 
			handleConnect(static_cast<const ConnectMsg&>(msg), client);
			break;
		case MsgType::DISCONNECT:
			handleDisconnect(static_cast<const DisconnectMsg&>(msg), client);
			break;
		default:
			std::cerr << "CLIENT ROOM: MSG TYPE NOT INFERABLE: " << msg.toString() << std::endl;
	}

}