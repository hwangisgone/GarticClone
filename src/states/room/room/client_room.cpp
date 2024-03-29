#include <iostream>

#include <client/client_handler.hpp>

#include "msg/msg_connection.hpp"
#include "msg/msg_start.hpp"
#include "client_connection.hpp"

#include <js_io/js_output.hpp>
#include <printdebug/debugging.h>

using namespace std;

void RoomState::requestDisconnect() {
	PlayerDisconnectMsg msg;
	ClientHandler::clientSendMsg(msg);
}

void RoomState::requestStart(){
	StartMsg msg;
	ClientHandler::clientSendMsg(msg);
}


void jsToLobby() {
	globalJsEval("room_toLobby()");
}

void jsToRoom() {
	globalJsEval("room_toRoom()");
}

void jsStartGame() {
	globalJsEval("room_toGame()");
}

void jsAddPlayer(const PlayerConnectMsg& msg) {
	globalJsEval("room_addPlayer(" + to_string(msg.playerID) + ",\"" + string(msg.name) + "\")");
}

void jsRemovePlayer(const PlayerDisconnectMsg& msg) {
	globalJsEval("room_removePlayer(" + to_string(msg.playerID) + ")");
}


void startTheGame(const StartMsg& msg, ClientHandler * client) {
	DEBUG_PRINT("  (StateRoom) Game started!!!");
	client->setState(new InGameState());
	jsStartGame();
	// Do something else here???
	// Get timer or set role
}
void ClientConn::handleConnect(const PlayerConnectMsg& msg, ClientHandler * client) {
	DEBUG_PRINT("  (StateRoom) Connection from " + std::string(msg.name));
	client->addPlayer(msg.playerID, msg.name);
	jsAddPlayer(msg);
}
void ClientConn::handleDisconnect(const PlayerDisconnectMsg& msg, ClientHandler * client) {
	if (client->meID != msg.playerID) {
		DEBUG_PRINT("  (StateRoom) Disconnection.");
		client->removePlayer(msg.playerID);
		jsRemovePlayer(msg);
	} else {
		DEBUG_PRINT("  (StateRoom) Disconnected.");
		client->setState(new LobbyState());
		jsToLobby();
	}
}

void ClientConn::backToRoom(ClientHandler * client) {
	DEBUG_PRINT("!!! Forced back to room !!!");
	client->setState(new RoomState());
	jsToRoom();
}


void RoomState::handleRecv(const BaseMsg& msg) {
	// - wait for host to start
	DEBUG_PRINT("  (StateRoom) " + msg.toString());

	switch (msg.type()) {
		case MsgType::CONNECT: 
			ClientConn::handleConnect(static_cast<const PlayerConnectMsg&>(msg), client);
			break;
		case MsgType::DISCONNECT:
			ClientConn::handleDisconnect(static_cast<const PlayerDisconnectMsg&>(msg), client);
			break;
		case MsgType::START_GAME:
			startTheGame(static_cast<const StartMsg&>(msg), client);
			break;
		default:
			std::cerr << "CLIENT ROOM: MSG TYPE NOT INFERABLE: " << msg.toString() << std::endl;
	}

}