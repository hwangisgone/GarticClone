#ifndef MSG_FORMAT_H
#define MSG_FORMAT_H

#include "type/msg_base.hpp"

struct MsgWrapper {
	int playerID;
	std::unique_ptr<BaseMsg> msg;
};

#endif