#include <iostream>

#include <client/client_handler.hpp>

#include "msg/msg_connection.hpp"
#include "msg/msg_start.hpp"

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



void startGame(const StartMsg& msg, ClientHandler * client) {
	DEBUG_PRINT("  (StateRoom) Game started!!!");
	client->setState(new InGameState());
}
void handleConnect(const PlayerConnectMsg& msg, ClientHandler * client) {
	DEBUG_PRINT("  (StateRoom) Connection from " + std::string(msg.name));
	client->addPlayer(msg.playerID, msg.name);
}
void handleDisconnect(const PlayerDisconnectMsg& msg, ClientHandler * client) {
	DEBUG_PRINT("  (StateRoom) Disconnection.");
	client->removePlayer(msg.playerID);
}



void jsAddPlayer(const PlayerConnectMsg& msg) {
	globalJsEval("room_addPlayer(" + to_string(msg.playerID) + ",\"" + string(msg.name) + "\")");
}

void jsRemovePlayer(const PlayerDisconnectMsg& msg) {
	globalJsEval("room_removePlayer(" + to_string(msg.playerID) + ")");
}

void RoomState::handleRecv(const BaseMsg& msg) {
	// - wait for host to start
	DEBUG_PRINT("  (StateRoom) " + msg.toString());

	switch (msg.type()) {
		case MsgType::CONNECT: 
			handleConnect(static_cast<const PlayerConnectMsg&>(msg), client);
			break;
		case MsgType::DISCONNECT:
			handleDisconnect(static_cast<const PlayerDisconnectMsg&>(msg), client);
			break;
		default:
			std::cerr << "CLIENT ROOM: MSG TYPE NOT INFERABLE: " << msg.toString() << std::endl;
	}

}