#ifndef MSG_INGAME_H
#define MSG_INGAME_H

#include <msg/msg_format.hpp>

struct Color {
	uint16_t red;
	uint16_t green;
	uint16_t blue;
};

// DrawMsg: [x 4|y 4|Color 6]
class DrawMsg : public BaseMsg {
private:
	uint32_t bodySize() const override { 
		return sizeof(uint32_t) + sizeof(uint32_t) + sizeof(color);
	}
public:
	uint32_t x;
	uint32_t y;
	char color[7];

	DrawMsg() : BaseMsg(MsgType::DRAW) {}

	void serializeBody(MsgBuffer& buff) const override;	// (2)
	void deserializeBody(MsgBuffer& buff) override;		// (3)
	std::string debugPrint() const override;			// (4)	// 1,2,3 are required
};

    
// AnswerMsg: [playerID 4|message 200]
class AnswerMsg : public BaseMsg {
private:
	uint32_t bodySize() const override;					// (1)
public:
	uint32_t playerID;
	char answer[200];

	AnswerMsg() : BaseMsg(MsgType::ANSWER) {}

	void serializeBody(MsgBuffer& buff) const override;	// (2)
	void deserializeBody(MsgBuffer& buff) override;		// (3)
	std::string debugPrint() const override;			// (4)	// 1,2,3 are required
};


// ScoreMsg: [playerID 4|score 4]
class ScoreMsg: public BaseMsg{
private:
	uint32_t bodySize() const override { 
		return sizeof(uint32_t) + sizeof(uint32_t); // 4 4
	}
public:
	uint32_t playerID;
	uint32_t score;

	ScoreMsg() : BaseMsg(MsgType::SCORE){}

	void serializeBody(MsgBuffer& buff) const override;	// (2)
	void deserializeBody(MsgBuffer& buff) override;		// (3)
	std::string debugPrint() const override;			// (4)	// 1,2,3 are required
};

#endif