#ifndef MSG_FORMAT_H
#define MSG_FORMAT_H

#include <type_traits>	// underlying_type
#include <string>
#include <cstring>		// memcpy
#include <memory>		// unique_ptr
#include "debugging.h"

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

	BaseMsg(MsgType type): msg_type(type), msg_length(0) {
		DEBUG_PRINT("BaseMsg called for type" + std::to_string(static_cast<std::underlying_type<MsgType>::type>(type)));
	}	// Syntax: Constructor

	BaseMsg(): msg_type(MsgType::NONE), msg_length(0) {}	// Default

	uint32_t calcLengthFromBody() {
		msg_length = 6 + bodySize()+1;	// [ 2 | 4 | content \0 ]
		return msg_length;
	}

	virtual void serializeBody(char * buffer) const {}	// Syntax: virtual means it should have subclass defining it (abstract method)
	virtual void deserializeBody(char * buffer) {}		// Doesn't need =0 because it may contain no body

	std::string toString() const;
	virtual std::string debugPrint() const { return ""; }
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
class AnswerMsg : public BaseMsg {
private:
    char message[900];
public:
    AnswerMsg() : BaseMsg(MsgType::ANSWER) {}

    void serializeBody(char *buffer) const override {
        memcpy(buffer, this->message, length());
    }

    void deserializeBody(char *buffer) override {
        memcpy(buffer, this->message, length());
    }

};


// ScoreMsg: [user 100|score 4]

class ScoreMsg: public BaseMsg{
private:
	int score;
public:
	ScoreMsg() : BaseMsg(MsgType::SCORE){}

};




#endif