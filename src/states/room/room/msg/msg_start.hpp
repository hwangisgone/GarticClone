#ifndef MSG_START_H
#define MSG_START_H

#include <msg/msg_format.hpp>

class StartMsg: public BaseMsg {
private:
	uint32_t bodySize() const override;
public:
	uint32_t timer;
	char word[50];
	
	StartMsg(): BaseMsg(MsgType::START_GAME) {}
	StartMsg(MsgType type): BaseMsg(type) {}	// NEXT_ROUND

	void serializeBody(MsgBuffer& buff) const override;
	void deserializeBody(MsgBuffer& buff) override;
	std::string debugPrint() const override;
};


#endif