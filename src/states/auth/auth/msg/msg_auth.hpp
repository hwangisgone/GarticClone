#ifndef MSG_AUTH_H
#define MSG_AUTH_H

#include <arpa/inet.h>
#include <msg/msg_format.hpp>

class AuthMsg: public BaseMsg {
private:
	uint32_t bodySize() const override { return sizeof(username) + strlen(password); };
	AuthMsg() = default;	// no class should use this
protected:
	AuthMsg(MsgType type): BaseMsg(type) {}	// Only derived class can use this. Login, Register

public:
	char username[50];
	char password[100];

	void serializeBody(MsgBuffer& buff) const override;
	void deserializeBody(MsgBuffer& buff) override;
	std::string debugPrint() const override;
};

class LoginMsg: public AuthMsg {	// Exactly the same as auth
public:
	LoginMsg(): AuthMsg(MsgType::LOGIN) {}
};

class RegisterMsg: public AuthMsg {	// Exactly the same as auth
public:
	RegisterMsg(): AuthMsg(MsgType::REGISTER) {}
};

#endif