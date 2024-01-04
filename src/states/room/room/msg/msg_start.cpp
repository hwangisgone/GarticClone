#include <string>

#include "msg_start.hpp"	// hpp for the ones with classes

using namespace std;

// START (same with NEXT_ROUND)
uint32_t StartMsg::bodySize() const { return sizeof(uint32_t) + strlen(word); }	// 4 bytes

void StartMsg::serializeBody(MsgBuffer& buff) const {
	buff.serializeField(this->timer);
	buff.serializeField(this->word, 50);
}

void StartMsg::deserializeBody(MsgBuffer& buff) {
	buff.deserializeField(&this->timer);
	buff.deserializeField(this->word, 50);
}

string StartMsg::debugPrint() const {
	return to_string(this->timer) + ":[" + this->word + "]";
}