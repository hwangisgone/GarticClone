#include <iostream>
#include <arpa/inet.h>		// sockaddr_in

#include <server/room_handler.hpp>

#include "msg/msg_start.hpp"
#include "room_connection.hpp"

#include <lobby/msg/msg_lobby.hpp>
#include <sockaddr_in/sockaddr_in_functions.hpp>
#include <msg/msg_sendrecv.h>
#include <printdebug/debugging.h>



void startGame(const StartMsg& msg, int playerID, RoomHandler * room) {
	if (room->playerMap.size() < 2) {
		TEST_PRINT("  (ServerRoom) Only 1 player in room. Cannot start game.");
		return;
	}

	if (room->host == playerID) {
		TEST_PRINT("  (ServerRoom) Game started!!!");
		StartMsg startmsg = msg;
		room->broadcast(startmsg);
		
		room->setState(new InGameState(room, 1));	// Broadcast NextRoundState
	}
}

void RoomConn::handleConnect(const JoinRoomMsg& msg, int playerID, RoomHandler * room) {
	DEBUG_PRINT("  (ServerRoom) Connection from " + formatSockAddrIn(msg.addr));

	for (const auto& pair : room->playerMap) {	// Send all players in the room to client
		PlayerConnectMsg othermsg;
		othermsg.playerID = pair.first;
		strncpy(othermsg.name, pair.second.account.playerName, 50);
		sendMsg(room->sockfd, (struct sockaddr*)&msg.addr, sizeof(msg.addr), othermsg);
	}

	room->addPlayer(playerID, msg.addr, *msg.account);
	
	PlayerConnectMsg thisplayermsg;
	thisplayermsg.playerID = playerID;
	strncpy(thisplayermsg.name, msg.account->playerName, 50);
	room->broadcast(thisplayermsg);
}

void RoomConn::handleDisconnect(int playerID, RoomHandler * room) {
	DEBUG_PRINT("  (ServerRoom) Disconnection.");
	room->removePlayer(playerID);

	PlayerDisconnectMsg thisplayermsg;
	thisplayermsg.playerID = playerID;
	room->broadcastExcept(thisplayermsg, playerID);
	// TODO: broadcast
}

void RoomState::handle(const BaseMsg& msg, int playerID) {
	// - wait for host to start
	DEBUG_PRINT("  (StateRoom) " + msg.toString());

	switch (msg.type()) {
		case MsgType::START_GAME: {
			startGame(static_cast<const StartMsg&> (msg), playerID,room);
			break;		
		}
		case MsgType::JOIN_ROOM: {
			RoomConn::handleConnect(static_cast<const JoinRoomMsg&>(msg), playerID, room);
			break;
		}
		case MsgType::DISCONNECT: {
			RoomConn::handleDisconnect(playerID, room);
			break;			
		}

		default:
			std::cerr << "SERVER ROOM: MSG TYPE NOT INFERABLE: " << msg.toString() << std::endl;
	}

}