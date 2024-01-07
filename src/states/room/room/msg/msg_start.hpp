#ifndef MSG_START_H
#define MSG_START_H

#include <msg/msg_format.hpp>

class StartMsg: public BaseMsg {
private:
	uint32_t bodySize() const override { return 0; };
public:
	StartMsg(): BaseMsg(MsgType::START_GAME) {}
};


#endif