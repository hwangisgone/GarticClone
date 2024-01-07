#include <iostream>

#include <client/client_handler.hpp>

#include <lobby/msg/msg_lobby.hpp>
#include <js_io/js_output.hpp>
#include <printdebug/debugging.h>

using namespace std;

void LobbyState::requestGetRooms() {
	GetRoomsMsg msg;
	ClientHandler::clientSendMsg(msg);
}

void LobbyState::requestCreateRoom(const char * name) {
	CreateRoomMsg msg;
	strncpy(msg.roomName, name, 50);

	ClientHandler::clientSendMsg(msg);
}

void LobbyState::requestJoinRoom(int roomID) {
	JoinRoomMsg msg;
	msg.roomID = roomID;

	ClientHandler::clientSendMsg(msg);
}

void jsAddRoom(const RoomListMsg& msg) {
	DEBUG_PRINT(" (LobbyState) Adding room to UI: " + to_string(msg.roomID) + ":" + string(msg.roomName));
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
		case MsgType::CREATE_ROOM:
			TEST_PRINT("-> (Create room success. Joined!!!!)");
			this->client->setState(new RoomState());
			// globalJsEval("lobby_setRoom(" + msg.roomID + ")");
			jsGoToRoom();
			break;
		case MsgType::JOIN_ROOM:	// Success
			TEST_PRINT("-> (Join room success!!!!)");
			this->client->setState(new RoomState());
			jsGoToRoom();
			break;
		default:
			cerr << "CLIENT LOBBY: MSG TYPE NOT INFERABLE: " << msg.toString() << endl;
	}
}