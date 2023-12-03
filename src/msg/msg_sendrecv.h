#ifndef MSG_SENDRECV_H
#define MSG_SENDRECV_H

#include <memory>		// unique_ptr
#include <sys/socket.h>

int sendMsg(int socket, struct sockaddr * targetAddr, socklen_t * targetAddrLen, const BaseMsg& msg);
std::unique_ptr<BaseMsg> recvMsg(int socket, struct sockaddr * targetAddr, socklen_t * targetAddrLen);

#endif