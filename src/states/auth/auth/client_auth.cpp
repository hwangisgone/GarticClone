#include <iostream>

#include <client/client_handler.hpp>
#include "msg/msg_auth.hpp"

#include <js_io/js_output.hpp>
#include <printdebug/debugging.h>

using namespace std;

void AuthState::requestLogin(char type, const char * name, const char * pass) {
	if (type == 0) {
		LoginMsg msg;
		strncpy(msg.username, name, 50);
		strncpy(msg.password, pass, 100);

		ClientHandler::clientSendMsg(msg);
	} else {
		RegisterMsg msg;
		strncpy(msg.username, name, 50);
		strncpy(msg.password, pass, 100);

		ClientHandler::clientSendMsg(msg);
	}
}

void jsIncorrect() {
	globalJsEval("auth_wrongPass()");
}

void jsUsernameUsed() {
	globalJsEval("auth_usernameUsed()");
}

void jsRegistered() {
	globalJsEval("auth_registered()");
}

void jsGoToLobby() {
	globalJsEval("auth_toLobby()");
}

void handleFail(const FailMsg& msg) {
	switch(msg.failtype()) {
		case MsgType::LOGIN:
			TEST_PRINT("-> (Wrong password or username)");
			jsIncorrect();
			break;
		case MsgType::REGISTER:
			TEST_PRINT("-> (Username already used)");
			jsUsernameUsed();
			break;
		default:
			cerr << "FAIL TYPE NOT INFERABLE: " << msg.toString() << endl;
			break;
	}
}

void auth_handleSuccess(const SuccessMsg& msg, ClientHandler * client) {
	switch(msg.successtype()) {
		case MsgType::LOGIN:
			TEST_PRINT("-> (Login success!!!!)");
			client->setState(new LobbyState());
			jsGoToLobby();
			break;
		case MsgType::REGISTER:
			TEST_PRINT("-> (Register success!!!!)");
			jsRegistered();
			break;
		default:
			cerr << "SUCCESS TYPE NOT INFERABLE: " << msg.toString() << endl;
			break;
	}
}

void AuthState::handleRecv(const BaseMsg& msg) {
	// - wait for host to start
	DEBUG_PRINT("(StateAuth) " + msg.toString());

	switch (msg.type()) {
		case MsgType::FAILURE: 
			handleFail(static_cast<const FailMsg&>(msg));
			break;
		case MsgType::SUCCESS:
			auth_handleSuccess(static_cast<const SuccessMsg&>(msg), this->client);
			break;
		default:
			cerr << "CLIENT AUTH: MSG TYPE NOT INFERABLE: " << msg.toString() << endl;
	}

}