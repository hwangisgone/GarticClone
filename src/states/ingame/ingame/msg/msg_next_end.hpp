#ifndef MSG_NEXT_END_H
#define MSG_NEXT_END_H

#include <room/msg/msg_start.hpp>
#include <msg/msg_format.hpp>

class NextRoundMsg: public StartMsg {	// Exactly the same as start
public:
	NextRoundMsg(): StartMsg(MsgType::NEXT_ROUND) {}
};

class EndMsg: public BaseMsg {
public:
	EndMsg(): BaseMsg(MsgType::END_GAME) {}
};

#endif