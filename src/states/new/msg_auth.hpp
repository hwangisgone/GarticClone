#ifndef MSG_AUTH_H
#define MSG_AUTH_H

#include <arpa/inet.h>
#include "msg/msg_format.hpp"

class AuthMsg: public BaseMsg {
private:
	uint32_t bodySize() const override;
public:
	char auth_type;		// 1: Login, 0: Register
	char username[50];
	char password[100];

	AuthMsg(): BaseMsg(MsgType::AUTH) {}

	void serializeBody(MsgBuffer& buff) const override;
	void deserializeBody(MsgBuffer& buff) override;
	std::string debugPrint() const override;
};

class RoomListMsg: public BaseMsg {
	// TODO:
public:
	uint32_t roomID;
	char roomName[50];

	RoomListMsg(): BaseMsg(MsgType::ROOM_LIST) {}

	// void serializeBody(MsgBuffer& buff) const override;
	// void deserializeBody(MsgBuffer& buff) override;
	// std::string debugPrint() const override;
};

#endif