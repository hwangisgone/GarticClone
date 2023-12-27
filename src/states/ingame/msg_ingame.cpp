#include <string>

#include "msg_ingame.hpp"	// hpp for the ones with classes

using namespace std;

// ************
// *** DRAW ***
// ************
// TODO: finish draw msg
// TODO: formalize all the serialize (since there's only 3 types: short, int and char[])

uint32_t AnswerMsg::bodySize() const { 
	return sizeof(uint32_t) + strlen(this->answer); // TODO: strlen or just plain 900
}

void DrawMsg::serializeBody(MsgBuffer& buff) const {
	buff.serializeField(this->playerID);
	buff.serializeField(this->clr, 3);
}

void DrawMsg::deserializeBody(MsgBuffer& buff) {
	buff.serializeField(this->playerID);
	buff.serializeField(this->clr, 3);
}

string DrawMsg::debugPrint() const {
	return "drawnotimplmentened";
}

// **************
// *** ANSWER ***
// **************
uint32_t AnswerMsg::bodySize() const { 
	return sizeof(uint32_t) + strlen(this->answer); // TODO: strlen or just plain 900
}

void AnswerMsg::serializeBody(MsgBuffer& buff) const {
	buff.serializeField(this->playerID);
	buff.serializeField(this->answer, 900);
}

void AnswerMsg::deserializeBody(MsgBuffer& buff) {
	buff.deserializeField(&this->playerID);
	buff.deserializeField(this->answer, 900);
}

string AnswerMsg::debugPrint() const {
	return to_string(this->playerID) 
		+ ":[" + string(this->answer) + "]";
}

// *************
// *** SCORE ***
// *************
void ScoreMsg::serializeBody(MsgBuffer& buff) const {
	buff.serializeField(this->playerID);
	buff.serializeField(this->score);
}

void ScoreMsg::deserializeBody(MsgBuffer& buff) {
	buff.deserializeField(&this->playerID);
	buff.deserializeField(&this->score);
}

string ScoreMsg::debugPrint() const {
	return to_string(this->playerID) 
		+ ":" + to_string(this->score);
}