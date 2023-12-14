#ifndef MSG_CONNECT_H
#define MSG_CONNECT_H

#include <arpa/inet.h>
#include "../msg_format.hpp"

class ConnectMsg: public BaseMsg {
private:
	uint32_t bodySize() const override;
public:
	uint32_t playerID;
	char name[50];
	sockaddr_in addr;	// Assigned during recv
	
	ConnectMsg(): BaseMsg(MsgType::CONNECT) {}

	void serializeBody(char * buffer) const override;
	void deserializeBody(char * buffer) override;
	std::string debugPrint() const override;
};

class DisconnectMsg: public BaseMsg {
private:
	uint32_t bodySize() const override;
public:
	uint32_t playerID;

	DisconnectMsg(): BaseMsg(MsgType::DISCONNECT) {}

	void serializeBody(char * buffer) const override;
	void deserializeBody(char * buffer) override;
	std::string debugPrint() const override;
};

#endif