#include <iostream>

#include "client/client_handler.hpp"

#include "msg_lobby.hpp"
#include "debugging.h"

using namespace std;

void LobbyState::requestJoinRoom(int roomID) {
	JoinRoomMsg msg;
	msg.roomID = roomID;

	ClientHandler::clientSendMsg(msg);
}

void LobbyState::handleRecv(const BaseMsg &msg)
{
	DEBUG_PRINT("  (LobbyState) " + msg.toString());

	switch (msg.type()) {
		case MsgType::JOIN_ROOM:	// Success
			break;
		default:
			cerr << "CLIENT LOBBY: MSG TYPE NOT INFERABLE: " << msg.toString() << endl;
	}
}