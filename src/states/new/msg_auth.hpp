#ifndef MSG_AUTH_H
#define MSG_AUTH_H

#include <arpa/inet.h>
#include "msg/msg_format.hpp"

class AuthMsg: public BaseMsg {
private:
	uint32_t bodySize() const override { return 1 + 50 + 100; };
public:
	char username[50];
	char password[100];

	AuthMsg(): BaseMsg(MsgType::AUTH) {}

	void serializeBody(MsgBuffer& buff) const override;
	void deserializeBody(MsgBuffer& buff) override;
	std::string debugPrint() const override;
};

// Signal only
class FailMsg: public BaseMsg {
public:
	FailMsg(): BaseMsg(MsgType::FAILURE) {}
};

#endif