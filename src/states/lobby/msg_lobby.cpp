#include <string>

#include "msg_lobby.hpp"

using namespace std;

uint32_t JoinRoomMsg::bodySize() const { return sizeof(uint32_t); } // 4 bytes

void JoinRoomMsg::serializeBody(MsgBuffer& buff) const {
	buff.serializeField(this->roomID);
}

void JoinRoomMsg::deserializeBody(MsgBuffer& buff) {
	buff.deserializeField(&this->roomID);
}

string JoinRoomMsg::debugPrint() const {
	return to_string(this->roomID);
}