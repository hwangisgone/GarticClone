#include <iostream>

#include <arpa/inet.h>		// sockaddr_in

#include "msg/types/msg_connect.hpp"
#include "msg/types/msg_transition.hpp"

#include "debugging.h"
#include "client_handler.hpp"


void AuthState::handleRecv(const BaseMsg& msg) {
	// - wait for host to start
	DEBUG_PRINT("  (StateAuth) " + msg.toString());

	switch (msg.type()) {
		// case MsgType::ROOM_LIST: 
		// 	handleConnect(static_cast<const ConnectMsg&>(msg), client);
		// 	break;
		// case MsgType::DISCONNECT:
		// 	handleDisconnect(static_cast<const DisconnectMsg&>(msg), client);
		// 	break;
		default:
			std::cerr << "CLIENT AUTH: MSG TYPE NOT INFERABLE: " << msg.toString() << std::endl;
	}

}