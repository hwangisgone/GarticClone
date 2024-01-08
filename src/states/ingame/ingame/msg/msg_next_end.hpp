#ifndef MSG_NEXT_END_H
#define MSG_NEXT_END_H

#include <msg/msg_format.hpp>

class NextRoundMsg: public BaseMsg {
private:
	uint32_t bodySize() const override { return sizeof(uint32_t) + sizeof(uint32_t) + strlen(word); }
public:
	uint32_t timer;
	uint32_t role;
	char word[50];

	NextRoundMsg(): BaseMsg(MsgType::NEXT_ROUND) {}

	void serializeBody(MsgBuffer& buff) const override;
	void deserializeBody(MsgBuffer& buff) override;
	std::string debugPrint() const override;
};

class EndMsg: public BaseMsg {
public:
	EndMsg(): BaseMsg(MsgType::END_GAME) {}
};

#endif