#include <string>

#include "msg_next_end.hpp"	// hpp for the ones with classes

using namespace std;

// START (NEXT_ROUND)


void NextRoundMsg::serializeBody(MsgBuffer& buff) const {
	buff.serializeField(this->timer);
	buff.serializeField(this->role);
	buff.serializeField(this->word, 50);
}

void NextRoundMsg::deserializeBody(MsgBuffer& buff) {
	buff.deserializeField(&this->timer);
	buff.deserializeField(&this->role);
	buff.deserializeField(this->word, 50);
}

string NextRoundMsg::debugPrint() const {
	return to_string(this->timer) + ":role=" + to_string(this->role) + ":[" + this->word + "]";
}

// IDK, maybe end here?