#include <string>

#include "msg_ingame.hpp"	// hpp for the ones with classes

using namespace std;

// ************
// *** DRAW ***
// ************
// TODO: finish draw msg
// TODO: formalize all the serialize (since there's only 3 types: short, int and char[])

void DrawMsg::serializeBody(MsgBuffer& buff) const {
	buff.serializeField(this->x);
	buff.serializeField(this->y);
	buff.serializeField(this->color, 7);
	buff.serializeField(this->size);
	buff.serializeField(&this->start, 1);
}

void DrawMsg::deserializeBody(MsgBuffer& buff) {
	buff.deserializeField(&this->x);
	buff.deserializeField(&this->y);
	buff.deserializeField(this->color, 7);
	buff.deserializeField(&this->size);
	buff.deserializeField(&this->start, 1);
}

string DrawMsg::debugPrint() const {
	//return "drawnotimplmentened";
	return to_string(this->x) + ":" + to_string(this->y) 
		+ ":#" + string(this->color) + "#";
}

// **************
// *** ANSWER ***
// **************
uint32_t AnswerMsg::bodySize() const { 
	return sizeof(uint32_t) + strlen(this->answer); // TODO: strlen or just plain 900
}

void AnswerMsg::serializeBody(MsgBuffer& buff) const {
	buff.serializeField(this->playerID);
	buff.serializeField(this->answer, 200);
}

void AnswerMsg::deserializeBody(MsgBuffer& buff) {
	buff.deserializeField(&this->playerID);
	buff.deserializeField(this->answer, 200);
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