#include <string>

#include "msg_auth.hpp"

using namespace std;

uint32_t AuthMsg::bodySize() const { return 1 + 50 + 100; } // 4 bytes

void AuthMsg::serializeBody(MsgBuffer& buff) const {
	buff.serializeField(&this->auth_type, 1);
	buff.serializeField(this->username, 50);
	buff.serializeField(this->password, 100);
}

void AuthMsg::deserializeBody(MsgBuffer& buff) {
	buff.deserializeField(&this->auth_type, 1);
	buff.deserializeField(this->username, 50);
	buff.deserializeField(this->password, 100);
}

string AuthMsg::debugPrint() const {
	return "[" + std::string(this->username) + "]"
		+ "[" + std::string(this->password) + "]";
}