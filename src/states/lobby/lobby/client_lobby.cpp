#include <iostream>

#include <client/client_handler.hpp>

#include <lobby/msg/msg_lobby.hpp>
#include <js_io/js_output.hpp>
#include <printdebug/debugging.h>

using namespace std;

void LobbyState::requestGetRooms() {
	GetRoomsMsg msg;
	ClientHandler::clientSendMsg(msg);

	// Refresh room list
	globalJsEval("lobby_refresh()");
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

void jsReturnToLogin() {
	globalJsEval("lobby_toLogin()");
}


void lobby_handleSuccess(const SuccessMsg& msg, ClientHandler * client) {
	switch(msg.successtype()) {
		case MsgType::CREATE_ROOM:
			TEST_PRINT("-> (Create room success.)");
			LobbyState::requestGetRooms();	// Refresh
			break;
		case MsgType::JOIN_ROOM:
			TEST_PRINT("-> (Join room success!!!!)");
			client->setState(new RoomState());
			jsGoToRoom();
			break;
		case MsgType::LOGOUT:
			TEST_PRINT("-> (Logged out anyways)");
			client->setState(new AuthState());
			jsReturnToLogin();
			break;
		default:
			cerr << "SUCCESS TYPE NOT INFERABLE: " << msg.toString() << endl;
			break;
	}
}


void LobbyState::handleRecv(const BaseMsg &msg)
{
	DEBUG_PRINT("  (LobbyState) " + msg.toString());

	switch (msg.type()) {
		case MsgType::ROOM_LIST:
			jsAddRoom(static_cast<const RoomListMsg&>(msg));
			break;
		case MsgType::SUCCESS:
			lobby_handleSuccess(static_cast<const SuccessMsg&>(msg), this->client);
			break;
		default:
			cerr << "CLIENT LOBBY: MSG TYPE NOT INFERABLE: " << msg.toString() << endl;
	}
}