#include <iostream>

#include "client/client_handler.hpp"

#include "msg_lobby.hpp"
#include "in_out/js_output.hpp"
#include "debugging.h"

using namespace std;

void LobbyState::requestJoinRoom(int roomID) {
	JoinRoomMsg msg;
	msg.roomID = roomID;

	ClientHandler::clientSendMsg(msg);
}

void jsAddRoom(const RoomListMsg& msg) {
	globalJsEval("lobby_addRoom(" + to_string(msg.roomID) + ",\"" + string(msg.roomName) + "\")");
}

void jsGoToRoom() {
	globalJsEval("lobby_toRoom()");
}

void LobbyState::handleRecv(const BaseMsg &msg)
{
	DEBUG_PRINT("  (LobbyState) " + msg.toString());

	switch (msg.type()) {
		case MsgType::ROOM_LIST:
			jsAddRoom(static_cast<const RoomListMsg&>(msg));
			break;
		case MsgType::JOIN_ROOM:	// Success
			DEBUG_PRINT(" (Join room success!!!!) ");
			this->client->setState(new RoomState());
			jsGoToRoom();
			break;
		default:
			cerr << "CLIENT LOBBY: MSG TYPE NOT INFERABLE: " << msg.toString() << endl;
	}
}