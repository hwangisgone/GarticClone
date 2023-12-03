#ifndef MSG_FORMAT_H
#define MSG_FORMAT_H

#include <string>
#include <memory>		// unique_ptr

enum class MsgType : uint16_t
{
	NONE = 0,
	START,
	END,
	LOBBY,
	NEXT_ROUND,
	CONNECT,
	DISCONNECT,

	DRAW,
	ANSWER,
	SCORE,
};

class BaseMsg {
private:
	MsgType msg_type;
	uint32_t msg_length;

protected:
	virtual uint32_t bodySize() const { return 0; };	// bodySize() used only for serialization

public:
	MsgType type() const { return msg_type; }			// Syntax: const means it won't change members (msg_type or length)
	uint32_t length() const { return msg_length; }
	void setTypeLength(MsgType type, uint32_t length) { 
		msg_type = type;
		msg_length = length;
	}

	BaseMsg(MsgType type): msg_type(type), msg_length(0) {}	// Syntax: Constructor
	BaseMsg(): msg_type(MsgType::NONE), msg_length(0) {}				// Default

	uint32_t calcLengthFromBody() const {
		// msg_length = 6 + bodySize()+1;	// [ 2 | 4 | content \0 ]
		return 6 + bodySize()+1;
	}

	std::string toString();

	virtual void serializeBody(char * buffer) const {}	// Syntax: virtual means it should have subclass defining it (abstract method)
	virtual void deserializeBody(char * buffer) {}		// Doesn't need =0 because it may contain no body

	virtual std::string debugPrint() { return ""; }
};


std::unique_ptr<BaseMsg> factoryProduceMsg(MsgType type);


class StartMsg: public BaseMsg {
// protected:
// 	uint32_t bodySize() override { return 0; }
public:
	StartMsg(): BaseMsg(MsgType::START) {}
// 	void serializeBody(char * buffer) override {}
// 	void deserializeBody(char * buffer) override {}
};


class EndMsg: public BaseMsg {
// protected:
// 	uint32_t bodySize() override { return 0; }
public:
	EndMsg(): BaseMsg(MsgType::END) {}
	// void serializeBody(char * buffer) override {}
	// void deserializeBody(char * buffer) override {}
};


class LobbyMsg: public BaseMsg {
// protected:
// 	uint32_t bodySize() override { return 0; }
public:
	LobbyMsg(): BaseMsg(MsgType::LOBBY) {}
	// void serializeBody(char * buffer) override {}
	// void deserializeBody(char * buffer) override {}
};


class NextRoundMsg: public BaseMsg {
// protected:
// 	uint32_t bodySize() override { return 0; }
public:
	NextRoundMsg(): BaseMsg(MsgType::NEXT_ROUND) {}
	// void serializeBody(char * buffer) override {}
	// void deserializeBody(char * buffer) override {}
};


class ConnectMsg: public BaseMsg {
protected:
	uint32_t bodySize() const override;
public:
	char name[50];

	ConnectMsg(): BaseMsg(MsgType::CONNECT) {}

	void serializeBody(char * buffer) const override;
	void deserializeBody(char * buffer) override;
	std::string debugPrint() override;
};


class DisconnectMsg: public BaseMsg {
// protected:
// 	uint32_t bodySize() override { return 0; }
public:
	DisconnectMsg(): BaseMsg(MsgType::DISCONNECT) {}
	// void serializeBody(char * buffer) override {}
	// void deserializeBody(char * buffer) override {}
};


class DrawMsg: public BaseMsg {
protected:
	// uint32_t bodySize() override { return 0; }
public:
	DrawMsg(): BaseMsg(MsgType::DRAW) {}	// Constructor
	// void serializeBody(char * buffer) override {}
	// void deserializeBody(char * buffer) override {}
};

// DrawMsg: [x 2|y 2|clr 4 (rgba)]
// AnswerMsg: [user 100|message 900]
// ScoreMsg: [user 100|score 4]





#endif