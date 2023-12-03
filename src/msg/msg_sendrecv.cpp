// #include <memory>		// unique_ptr
// #include <sys/socket.h>

#include "msg_format.hpp"
#include "msg_serialize.h"
#include "msg_sendrecv.h"

#include <cstring>
#include <iostream>
// DrawMsg: [x 2|y 2|clr 4 (rgba)]
// AnswerMsg: [user 100|message 900]
// ScoreMsg: [user 100|score 4]

#define BUFFER_SIZE 1024

char onceBuffer[BUFFER_SIZE];
int sendMsg(int socket, struct sockaddr * targetAddr, socklen_t * targetAddrLen, const BaseMsg& msg) {
	// Clear onceBuffer and serializing
	memset(onceBuffer, 0, sizeof(onceBuffer));
	serializeMsg(onceBuffer, msg);

	// Need refactoring
	ssize_t sentBytes = sendto(socket, onceBuffer, msg.length(), 0, targetAddr, *targetAddrLen);
	if (sentBytes == -1) {
		std::cerr << "Error sending data" << std::endl;
		return -1;
	}

	// Need checking??
	if (sentBytes != msg.length()) {
		std::cout << "ERROR: SEND BYTES != MSG LENGTH: " << sentBytes << " != " << msg.length() << "\n";
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
	if (receivedBytes != msg->length()) {
		std::cout << "ERROR: RECEIVED BYTES != MSG LENGTH: " << receivedBytes << " != " << msg->length() << "\n";
	}

	return msg;
}