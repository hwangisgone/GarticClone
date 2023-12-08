// #include <memory>		// unique_ptr
// #include <sys/socket.h>

#include "msg_format.hpp"
#include "msg_serialize.h"
#include "msg_sendrecv.h"
#include "debugging.h"

#include <cstring>
#include <iostream>
// DrawMsg: [x 2|y 2|clr 4 (rgba)]
// AnswerMsg: [user 100|message 900]
// ScoreMsg: [user 100|score 4]

#define BUFFER_SIZE 1024

char onceBuffer[BUFFER_SIZE];
int sendMsg(int socket, struct sockaddr * targetAddr, socklen_t targetAddrLen, BaseMsg& msg) {
	// Clear onceBuffer and serializing
	memset(onceBuffer, 0, sizeof(onceBuffer));

	msg.calcLengthFromBody();
	serializeMsg(onceBuffer, msg);

	DEBUG_PRINT(msg.toString());

	// Need refactoring
	ssize_t sentBytes = sendto(socket, onceBuffer, msg.length(), 0, targetAddr, targetAddrLen);
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
	ssize_t receivedBytes = recvfrom(socket, onceBuffer, BUFFER_SIZE, 0, targetAddr, targetAddrLen);
	if (receivedBytes == -1) {
		std::cerr << "Error receiving data" << std::endl;
		return nullptr;
	}
	onceBuffer[receivedBytes] = '\0';

	std::unique_ptr<BaseMsg> msg = deserializeMsg(onceBuffer);

	// Need checking??
	if (msg) {
		DEBUG_PRINT(msg->toString());
		if (receivedBytes != msg->length()) {
			std::cerr << "ERROR: RECEIVED BYTES != MSG LENGTH: " << receivedBytes << " != " << msg->length() << "\n";
		}
	}

	return msg;
}