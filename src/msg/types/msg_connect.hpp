#ifndef MSG_CONNECT_H
#define MSG_CONNECT_H

#include <arpa/inet.h>
#include "../msg_format.hpp"

class ConnectMsg: public BaseMsg {
protected:
	uint32_t bodySize() const override;
public:
	uint32_t playerID;
	sockaddr_in addr;	// Assigned during recv
	
	ConnectMsg(): BaseMsg(MsgType::CONNECT) {}

	void serializeBody(char * buffer) const override;
	void deserializeBody(char * buffer) override;
	std::string debugPrint() const override;
};

class DisconnectMsg: public BaseMsg {
protected:
	uint32_t bodySize() const override;
public:
	uint32_t playerID;

	DisconnectMsg(): BaseMsg(MsgType::DISCONNECT) {}

	void serializeBody(char * buffer) const override;
	void deserializeBody(char * buffer) override;
	std::string debugPrint() const override;
};

#endif