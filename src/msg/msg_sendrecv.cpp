// #include <memory>		// unique_ptr
#include <sys/socket.h>

#include "msg_format.hpp"
#include "msg_serialize.hpp"
#include "msg_sendrecv.h"
#include "debugging.h"

#include <cstring>
#include <iostream>

MsgBuffer sendrecvBuffer;

int sendMsg(int socket, struct sockaddr * targetAddr, socklen_t targetAddrLen, BaseMsg& msg) {
	msg.calcLengthFromBody();
	sendrecvBuffer.serializeMsg(msg);

	DEBUG_PRINT(msg.toString());

	// Need refactoring
	ssize_t sentBytes = sendto(socket, sendrecvBuffer.onceBuffer, msg.length(), 0, targetAddr, targetAddrLen);
	if (sentBytes < 0) {
		std::cerr << "Error sending data" << std::endl;
		return -1;
	}

	// Need checking??
	if (sentBytes != msg.length()) {
		std::cerr << "ERROR: SEND BYTES != MSG LENGTH: " << sentBytes << " != " << msg.length() << "\n";
	}

	return 0;
}

std::unique_ptr<BaseMsg> recvMsg(int socket, struct sockaddr * targetAddr, socklen_t * targetAddrLen) {
	// targetAddr & targetAddrLen may be nullptr
	ssize_t receivedBytes = recvfrom(socket, sendrecvBuffer.onceBuffer, BUFFER_SIZE, 0, targetAddr, targetAddrLen);
	if (receivedBytes == -1) {
		// DEBUG_COUT("\rError receiving data.\n");
		return nullptr;
	}
	sendrecvBuffer.onceBuffer[receivedBytes] = '\0';

	std::unique_ptr<BaseMsg> msg = sendrecvBuffer.deserializeMsg();

	// Need checking??
	if (msg) {
		DEBUG_PRINT(msg->toString());
		if (receivedBytes != msg->length()) {
			std::cerr << "ERROR: RECEIVED BYTES != MSG LENGTH: " << receivedBytes << " != " << msg->length() << "\n";
		}
	}

	return msg;
}