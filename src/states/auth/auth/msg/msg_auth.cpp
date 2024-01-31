#include <string>

#include "msg_auth.hpp"

using namespace std;

 // 4 bytes
void AuthMsg::serializeBody(MsgBuffer& buff) const {
	buff.serializeField(this->username, 50);
	buff.serializeField(this->password, 100);
}

void AuthMsg::deserializeBody(MsgBuffer& buff) {
	buff.deserializeField(this->username, 50);
	buff.deserializeField(this->password, 100);
}

string AuthMsg::debugPrint() const {
	return "[" + std::string(this->username) + "]"
		+ "[" + std::string(this->password) + "]";
}



void AccountInfoMsg::serializeBody(MsgBuffer& buff) const {
	buff.serializeField(this->playerID);
}

void AccountInfoMsg::deserializeBody(MsgBuffer& buff) {
	buff.deserializeField(&this->playerID);
}

string AccountInfoMsg::debugPrint() const {
	return to_string(this->playerID);
}