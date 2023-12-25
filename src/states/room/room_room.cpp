#include <iostream>
#include <arpa/inet.h>		// sockaddr_in

#include "server/room_handler.hpp"

#include "states/lobby/msg_lobby.hpp"
#include "msg_connection.hpp"
#include "msg_start.hpp"

#include "msg/msg_sendrecv.h"
#include "debugging.h"

#include "sockaddr_in/sockaddr_in_functions.h"



void startGame(const StartMsg& msg, int playerID, RoomHandler * room) {
	if (room->host == playerID) {
		DEBUG_PRINT("  (StateRoom) Game started!!!");
		room->setState(new InGameState());
	}
}

void handleConnect(const JoinRoomMsg& msg, int playerID, RoomHandler * room) {
	DEBUG_PRINT("  (StateRoom) Connection from " + formatSockAddrIn(msg.addr));

	for (const auto& pair : room->playerMap) {	// Send all players in the room to client
		PlayerConnectMsg othermsg;
		othermsg.playerID = pair.first;
		othermsg.name = pair.second.name;
		sendMsg(room->sockfd, (struct sockaddr*)&msg.addr, sizeof(msg.addr), othermsg);
	}

	room->addPlayer(playerID, msg.addr);

	PlayerConnectMsg thisplayermsg;
	thisplayermsg.playerID = playerID;
	strcpy(thisplayermsg.name, );
	room->broadcastExcept(thisplayermsg, playerID);
	// TODO: broadcast
}

void handleDisconnect(int playerID, RoomHandler * room) {
	DEBUG_PRINT("  (StateRoom) Disconnection.");
	room->removePlayer(playerID);
	// TODO: broadcast
}

void RoomState::handle(const BaseMsg& msg, int playerID) {
	// - wait for host to start
	DEBUG_PRINT("  (StateRoom) " + msg.toString());

	switch (msg.type()) {
		case MsgType::JOIN_ROOM: 
			handleConnect(static_cast<const JoinRoomMsg&>(msg), playerID, room);
			break;
		case MsgType::DISCONNECT:
			handleDisconnect(playerID, room);
			break;
		default:
			std::cerr << "SERVER ROOM: MSG TYPE NOT INFERABLE: " << msg.toString() << std::endl;
	}

}