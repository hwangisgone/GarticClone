#include <string>
#include <type_traits>	// underlying_type

#include "msg_base.hpp"

using namespace std;

string BaseMsg::toString() const {
	return "[" + to_string(static_cast<underlying_type<MsgType>::type>(msg_type))
		+ ":" + to_string(msg_length)
		+ "]:" + debugPrint();
}



// Success
void SuccessMsg::serializeBody(MsgBuffer& buff) const {
	buff.serializeField(static_cast<underlying_type<MsgType>::type>(this->result_type));
}
void SuccessMsg::deserializeBody(MsgBuffer& buff) {
	uint16_t deserial;
	buff.deserializeField(&deserial);
	this->result_type = static_cast<MsgType>(deserial);
}
string SuccessMsg::debugPrint() const {
	return "SUCCESS! [" + to_string(static_cast<underlying_type<MsgType>::type>(this->result_type)) + "]";
}


// Failure
void FailMsg::serializeBody(MsgBuffer& buff) const {
	buff.serializeField(static_cast<underlying_type<MsgType>::type>(this->result_type));
}
void FailMsg::deserializeBody(MsgBuffer& buff) {
	uint16_t deserial;
	buff.deserializeField(&deserial);
	this->result_type = static_cast<MsgType>(deserial);
}
string FailMsg::debugPrint() const {
	return "FAILED... [" + to_string(static_cast<underlying_type<MsgType>::type>(this->result_type)) + "]";
}

