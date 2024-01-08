#ifndef MSG_LOBBY_H
#define MSG_LOBBY_H

#include <arpa/inet.h>
#include <msg/msg_format.hpp>
#include <types/playeraccount.hpp>

class GetRoomsMsg: public BaseMsg {
private:
	uint32_t bodySize() const override { return 0; };
public:
	GetRoomsMsg(): BaseMsg(MsgType::GET_ROOMS) {}
};

class RoomListMsg: public BaseMsg {
private:
	uint32_t bodySize() const override { return sizeof(uint32_t) + sizeof(roomName); };
public:
	uint32_t roomID;
	char roomName[50];

	RoomListMsg(): BaseMsg(MsgType::ROOM_LIST) {}

	void serializeBody(MsgBuffer& buff) const override;
	void deserializeBody(MsgBuffer& buff) override;
	std::string debugPrint() const override;
};


class CreateRoomMsg: public BaseMsg {
private:
	uint32_t bodySize() const override { return 50; };
public:
	char roomName[50];
	
	CreateRoomMsg(): BaseMsg(MsgType::CREATE_ROOM) {}

	void serializeBody(MsgBuffer& buff) const override;
	void deserializeBody(MsgBuffer& buff) override;
	std::string debugPrint() const override;
};

class JoinRoomMsg: public BaseMsg {
private:
	uint32_t bodySize() const override { return sizeof(uint32_t); } // 4 bytes
public:
	uint32_t roomID;

	const PlayerAccount * account;	// Assigned during recv
	sockaddr_in addr;				// Assigned during recv

	JoinRoomMsg(): BaseMsg(MsgType::JOIN_ROOM) {}

	void serializeBody(MsgBuffer& buff) const override;
	void deserializeBody(MsgBuffer& buff) override;
	std::string debugPrint() const override;
};




#endif