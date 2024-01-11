#ifndef MSG_CONNECTION_H
#define MSG_CONNECTION_H

#include <msg/msg_format.hpp>

class PlayerConnectMsg: public BaseMsg {
private:
	uint32_t bodySize() const override { return sizeof(uint32_t) + sizeof(name); };
public:
	uint32_t playerID;
	char name[50];
	
	PlayerConnectMsg(): BaseMsg(MsgType::CONNECT) {}

	void serializeBody(MsgBuffer& buff) const override;
	void deserializeBody(MsgBuffer& buff) override;
	std::string debugPrint() const override;
};


class PlayerDisconnectMsg: public BaseMsg {
private:
	uint32_t bodySize() const override { return sizeof(uint32_t); }
public:
	uint32_t playerID;	// Added later

	PlayerDisconnectMsg(): BaseMsg(MsgType::DISCONNECT) {}

	void serializeBody(MsgBuffer& buff) const override;
	void deserializeBody(MsgBuffer& buff) override;
	std::string debugPrint() const override;
};

class BackToRoomMsg: public BaseMsg {
private:
	uint32_t bodySize() const override { return 0; };
public:
	BackToRoomMsg(): BaseMsg(MsgType::BACK_TO_ROOM) {}
};

#endif