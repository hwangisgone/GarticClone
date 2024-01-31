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

class LogoutMsg: public BaseMsg {
private:
	uint32_t bodySize() const override { return 0; };
public:
	LogoutMsg(): BaseMsg(MsgType::LOGOUT) {}
};


// AccountInfoMsg: [playerID 4|...]
class AccountInfoMsg: public BaseMsg {
private:
	uint32_t bodySize() const override { return sizeof(uint32_t); } // 4 
public:
	uint32_t playerID;

	AccountInfoMsg() : BaseMsg(MsgType::ACC_INFO){}

	void serializeBody(MsgBuffer& buff) const override;	// (2)
	void deserializeBody(MsgBuffer& buff) override;		// (3)
	std::string debugPrint() const override;			// (4)	// 1,2,3 are required
};

#endif