#ifndef MSG_INGAME_H
#define MSG_INGAME_H

#include "../msg_format.hpp"

// AnswerMsg: [playerID 4|message 900]
class AnswerMsg : public BaseMsg {
private:
	uint32_t bodySize() const override;					// (1)
public:
	uint32_t playerID;
    char message[900];
    AnswerMsg() : BaseMsg(MsgType::ANSWER) {}

    void serializeBody(char *buffer) const override;	// (2)
    void deserializeBody(char *buffer) override;		// (3)
    std::string debugPrint() const override;			// (4)	// 1,2,3 are required
};


// ScoreMsg: [playerID 4|score 4]
class ScoreMsg: public BaseMsg{
// private:
// 	uint32_t bodySize() const override;
public:
	int score;
	ScoreMsg() : BaseMsg(MsgType::SCORE){}

};

class NextRoundMsg: public BaseMsg {
// private:
// 	uint32_t bodySize() override { return 0; }
public:
	NextRoundMsg(): BaseMsg(MsgType::NEXT_ROUND) {}
	// void serializeBody(char * buffer) override {}
	// void deserializeBody(char * buffer) override {}
};

#endif