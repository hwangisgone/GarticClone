#ifndef MSG_TRANSITION_H
#define MSG_TRANSITION_H

#include "../msg_format.hpp"

class StartMsg: public BaseMsg {
// private:
// 	uint32_t bodySize() override { return 0; }
public:
	StartMsg(): BaseMsg(MsgType::START) {}
// 	void serializeBody(char * buffer) override {}
// 	void deserializeBody(char * buffer) override {}
};


class EndMsg: public BaseMsg {
// private:
// 	uint32_t bodySize() override { return 0; }
public:
	EndMsg(): BaseMsg(MsgType::END) {}
	// void serializeBody(char * buffer) override {}
	// void deserializeBody(char * buffer) override {}
};


class LobbyMsg: public BaseMsg {
// private:
// 	uint32_t bodySize() override { return 0; }
public:
	LobbyMsg(): BaseMsg(MsgType::LOBBY) {}
	// void serializeBody(char * buffer) override {}
	// void deserializeBody(char * buffer) override {}
};

// DrawMsg: [x 2|y 2|clr 6 (rgba)]
class DrawMsg: public BaseMsg {
private:
	// uint32_t bodySize() override { return 0; }
public:
	DrawMsg(): BaseMsg(MsgType::DRAW) {}	// Constructor
	// void serializeBody(char * buffer) override {}
	// void deserializeBody(char * buffer) override {}
};

#endif