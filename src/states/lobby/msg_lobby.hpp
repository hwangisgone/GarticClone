#ifndef MSG_LOBBY_H
#define MSG_LOBBY_H

#include <arpa/inet.h>
#include "msg/msg_format.hpp"

// TODO: implement this?
class CreateRoomMsg: public BaseMsg {
public:
	CreateRoomMsg(): BaseMsg(MsgType::CREATE_ROOM) {}
};

class JoinRoomMsg: public BaseMsg {
private:
	uint32_t bodySize() const override;
public:
	uint32_t roomID;

	char name[50];		// Assigned during recv
	sockaddr_in addr;	// Assigned during recv

	JoinRoomMsg(): BaseMsg(MsgType::JOIN_ROOM) {}

	void serializeBody(MsgBuffer& buff) const override;
	void deserializeBody(MsgBuffer& buff) override;
	std::string debugPrint() const override;
};

#endif