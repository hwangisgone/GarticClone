#include <iostream>

#include <arpa/inet.h>		// sockaddr_in

#include "msg/msg_format.hpp"
#include "msg/msg_sendrecv.h"
#include "debugging.h"

#include "sockaddr_in/sockaddr_in_functions.h"
#include "room_handler.hpp"

using namespace std;

void startGame(const StartMsg& msg, int playerID, RoomHandler * room) {
	if (room->host == playerID) {
		cout << "Game started!" << endl;
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
			cerr << "SERVER ROOM: MSG TYPE NOT INFERABLE: " << msg.toString() << endl;
	}

}