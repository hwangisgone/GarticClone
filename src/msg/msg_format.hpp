#ifndef MSG_FORMAT_H
#define MSG_FORMAT_H

#include <type_traits>	// underlying_type
#include <string>
#include <cstring>		// memcpy
#include <memory>		// unique_ptr
#include "debugging.h"

#include "msg_serialize.hpp"

enum class MsgType : uint16_t
{
	NONE = 0,
	AUTH,
	SUCCESS,	// Unused
	FAILURE,
	ROOM_LIST,
	CREATE_ROOM,
	JOIN_ROOM,
	DESTROY_ROOM,
	CONNECT,
	DISCONNECT,

	START_GAME,
	END_GAME,
	NEXT_ROUND,
	DRAW,
	ANSWER,
	SCORE,
};

class BaseMsg {
private:
	MsgType msg_type;
	uint32_t msg_length;
	virtual uint32_t bodySize() const { DEBUG_PRINT("BaseMsg::bodySize() WHY?"); return 0; };	// bodySize() used only for serialization

public:
	MsgType type() const { return msg_type; }			// Syntax: const means it won't change members (msg_type or length)
	uint32_t length() const { return msg_length; }

	void setLength(uint32_t length) {
		msg_length = length;
	}

	BaseMsg(MsgType type): msg_type(type), msg_length(0) {
		//	DEBUG_PRINT("BaseMsg called for type" + std::to_string(static_cast<std::underlying_type<MsgType>::type>(type)));
	}	// Syntax: Constructor;
	BaseMsg(): msg_type(MsgType::NONE), msg_length(0) {}	// Default

	uint32_t calcLengthFromBody() {
		msg_length = 6 + bodySize()+1;	// [ 2 | 4 | content \0 ]
		return msg_length;
	}

	virtual void serializeBody(MsgBuffer& buff) const {}	// Syntax: virtual means it should have subclass defining it (abstract method)
	virtual void deserializeBody(MsgBuffer& buff) {}		// Doesn't need =0 because it may contain no body

	std::string toString() const;
	virtual std::string debugPrint() const { return ""; }
};


std::unique_ptr<BaseMsg> factoryProduceMsg(MsgType type);

struct MsgWrapper {
	int playerID;
	std::unique_ptr<BaseMsg> msg;
};

#endif