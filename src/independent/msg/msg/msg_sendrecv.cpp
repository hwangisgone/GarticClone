// #include <memory>		// unique_ptr
#include <sys/socket.h>

#include "msg_format.hpp"
#include "msg_sendrecv.h"

#include <printdebug/debugging.h>

#include <cstring>
#include <iostream>

MsgBuffer sendrecvBuffer;

int sendMsg(int socket, struct sockaddr * targetAddr, socklen_t targetAddrLen, BaseMsg& msg) {
	msg.calcLengthFromBody();
	sendrecvBuffer.serializeMsg(msg);

	DEBUG_PRINT("send " + msg.toString());

	// Need refactoring
	ssize_t sentBytes = sendto(socket, sendrecvBuffer.onceBuffer, msg.length(), 0, targetAddr, targetAddrLen);
	if (sentBytes < 0) {
		DEBUG_PRINT("Error sending data");
		return -1;
	}

	// Need checking??
	if (sentBytes != msg.length()) {
		DEBUG_PRINT("ERROR: SEND BYTES != MSG LENGTH: " + std::to_string(sentBytes) + " != " + std::to_string(msg.length()) );
	}

	return 0;
}

#ifdef COLORED_MSG
	#define MAGENTA_MSG(x) "\033[95m" + x + "\033[0m"
#else
	#define MAGENTA_MSG(x) x
#endif

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
		DEBUG_PRINT(MAGENTA_MSG( "recv " + msg->toString() ));	// TODO: Make this colored?
		if (receivedBytes != msg->length()) {
			DEBUG_PRINT("ERROR: RECEIVED BYTES != MSG LENGTH: " + std::to_string(receivedBytes) + " != " + std::to_string(msg->length()) );
		}
	}

	return msg;
}