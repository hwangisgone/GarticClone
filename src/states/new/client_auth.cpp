#include <iostream>

#include "client/client_handler.hpp"

#include "msg_auth.hpp"
#include "debugging.h"

using namespace std;

void AuthState::requestLogin(char type, const char * name, const char * pass) {
	AuthMsg msg;
	msg.auth_type = type;
	strncpy(msg.username, name, 50);
	strncpy(msg.password, pass, 100);

	ClientHandler::clientSendMsg(msg);
}

void AuthState::handleRecv(const BaseMsg& msg) {
	// - wait for host to start
	DEBUG_PRINT("  (StateAuth) " + msg.toString());

	switch (msg.type()) {
		case MsgType::FAILURE: 
		break;
		case MsgType::ROOM_LIST:
			
		break;
		default:
			cerr << "CLIENT AUTH: MSG TYPE NOT INFERABLE: " << msg.toString() << endl;
	}

}