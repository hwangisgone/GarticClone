#include <iostream>

#include "client/client_handler.hpp"

#include "msg_auth.hpp"
#include "in_out/js_output.hpp"
#include "debugging.h"

using namespace std;

void AuthState::requestLogin(char type, const char * name, const char * pass) {
	AuthMsg msg;
	msg.auth_type = type;
	strncpy(msg.username, name, 50);
	strncpy(msg.password, pass, 100);

	ClientHandler::clientSendMsg(msg);
}

void jsGoToLobby() {
	globalJsEval("auth_toLobby()");
}

void AuthState::handleRecv(const BaseMsg& msg) {
	// - wait for host to start
	DEBUG_PRINT("  (StateAuth) " + msg.toString());

	switch (msg.type()) {
		case MsgType::FAILURE: 
			DEBUG_PRINT(" (Wrong password or username) ");
			break;
		case MsgType::AUTH:
			DEBUG_PRINT(" (Login success!!!!) ");
			this->client->setState(new LobbyState());
			jsGoToLobby();
			break;
		default:
			cerr << "CLIENT AUTH: MSG TYPE NOT INFERABLE: " << msg.toString() << endl;
	}

}