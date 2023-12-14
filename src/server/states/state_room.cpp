#include <iostream>

#include <arpa/inet.h>		// sockaddr_in

#include "msg/types/msg_connect.hpp"
#include "msg/types/msg_transition.hpp"

#include "msg/msg_sendrecv.h"
#include "debugging.h"

#include "sockaddr_in/sockaddr_in_functions.h"
#include "room_handler.hpp"


void startGame(const StartMsg& msg, int playerID, RoomHandler * room) {
	if (room->host == playerID) {
		DEBUG_PRINT("  (StateRoom) Game started!!!");
		room->setState(new InGameState());
	}
}

void handleConnect(const ConnectMsg& msg, int playerID, RoomHandler * room) {
	DEBUG_PRINT("  (StateRoom) Connection from " + formatSockAddrIn(msg.addr));
	room->addPlayer(playerID, msg.addr);
}

void handleDisconnect(int playerID, RoomHandler * room) {
	DEBUG_PRINT("  (StateRoom) Disconnection.");
	room->removePlayer(playerID);
}

void RoomState::handle(const BaseMsg& msg, int playerID) {
	// - wait for host to start
	DEBUG_PRINT("  (StateRoom) " + msg.toString());

	switch (msg.type()) {
		case MsgType::CONNECT: 
			handleConnect(static_cast<const ConnectMsg&>(msg), playerID, room);
			break;
		case MsgType::DISCONNECT:
			handleDisconnect(playerID, room);
			break;
		default:
			std::cerr << "SERVER ROOM: MSG TYPE NOT INFERABLE: " << msg.toString() << std::endl;
	}

}