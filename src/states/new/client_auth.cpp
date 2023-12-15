#include <iostream>

#include "client_auth.hpp"

#include "msg_auth.hpp"
#include "debugging.h"

using namespace std;

void AuthState::handleRecv(const BaseMsg& msg) {
	// - wait for host to start
	DEBUG_PRINT("  (StateAuth) " + msg.toString());

	switch (msg.type()) {
		// case MsgType::FAILURE: 
		// break;
		// case MsgType::ROOM_LIST: 
		// break;
		default:
			cerr << "CLIENT AUTH: MSG TYPE NOT INFERABLE: " << msg.toString() << endl;
	}

}