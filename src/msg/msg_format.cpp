#include <iostream>
#include <cstdint>
#include <cstring>

#include <type_traits>	// underlying_type
#include <memory>		// unique_ptr

#include "msg_format.hpp"	// hpp for the ones with classes

using namespace std;

// BASE
string BaseMsg::toString() {
	return	to_string(static_cast<underlying_type<MsgType>::type>(msg_type))
		+ ":" + to_string(msg_length)
		+ ":" + debugPrint();
}

// Add to this if you want to add more type (used for deserializing)
unique_ptr<BaseMsg> factoryProduceMsg(MsgType type) {
	switch(type) {
		case MsgType::START: 		return make_unique<StartMsg>();
		case MsgType::END:			return make_unique<EndMsg>();
		case MsgType::LOBBY:		return make_unique<LobbyMsg>();
		case MsgType::NEXT_ROUND:	return make_unique<NextRoundMsg>();
		case MsgType::CONNECT:		return make_unique<ConnectMsg>();
		case MsgType::DISCONNECT:	return make_unique<DisconnectMsg>();

		case MsgType::DRAW:			return make_unique<DrawMsg>();
		default:			return nullptr;
	}
}


// CONNECT
uint32_t ConnectMsg::bodySize() const { 
	return strlen(name); 
}

void ConnectMsg::serializeBody(char * buffer) const {
	strncpy(buffer, name, 50);
}

void ConnectMsg::deserializeBody(char * buffer) {
	strncpy(name, buffer, 50);
}

string ConnectMsg::debugPrint() {
	return name;
}