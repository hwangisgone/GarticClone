#include <string>

#include "msg_connection.hpp"	// hpp for the ones with classes

using namespace std;

// CONNECT 
uint32_t PlayerConnectMsg::bodySize() const { return sizeof(uint32_t); }	// 4 bytes

void PlayerConnectMsg::serializeBody(MsgBuffer& buff) const {
	buff.serializeField(this->playerID);
	buff.serializeField(this->name, 50);
}

void PlayerConnectMsg::deserializeBody(MsgBuffer& buff) {
	buff.deserializeField(&this->playerID);
	buff.deserializeField(this->name, 50);
}

string PlayerConnectMsg::debugPrint() const {
	return to_string(this->playerID) + ":[" + this->name + "]";
}


// & DISCONNECT (They're the same)
uint32_t PlayerDisconnectMsg::bodySize() const { return sizeof(uint32_t); } // 4 bytes

void PlayerDisconnectMsg::serializeBody(MsgBuffer& buff) const {
	buff.serializeField(this->playerID);
}

void PlayerDisconnectMsg::deserializeBody(MsgBuffer& buff) {
	buff.deserializeField(&this->playerID);
}

string PlayerDisconnectMsg::debugPrint() const {
	return to_string(this->playerID);
}