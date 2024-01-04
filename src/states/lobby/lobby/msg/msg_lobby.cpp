#include <string>

#include "msg_lobby.hpp"

using namespace std;

// RoomList
void RoomListMsg::serializeBody(MsgBuffer& buff) const {
	buff.serializeField(this->roomID);
	buff.serializeField(this->roomName, 50);
}
void RoomListMsg::deserializeBody(MsgBuffer& buff) {
	buff.deserializeField(&this->roomID);
	buff.deserializeField(this->roomName, 50);
}
string RoomListMsg::debugPrint() const {
	return "[" + std::to_string(this->roomID) + "]"
		+ "[" + std::string(this->roomName) + "]";
}


// CreateRoom
void CreateRoomMsg::serializeBody(MsgBuffer& buff) const {
	buff.serializeField(this->roomName, 50);
}
void CreateRoomMsg::deserializeBody(MsgBuffer& buff) {
	buff.deserializeField(this->roomName, 50);
}
string CreateRoomMsg::debugPrint() const {
	return "[" + string(this->roomName) + "]";
}


// JoinRoom
void JoinRoomMsg::serializeBody(MsgBuffer& buff) const {
	buff.serializeField(this->roomID);
}
void JoinRoomMsg::deserializeBody(MsgBuffer& buff) {
	buff.deserializeField(&this->roomID);
}
string JoinRoomMsg::debugPrint() const {
	return to_string(this->roomID);
}