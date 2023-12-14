#include <cstdint>
#include <cstring>

#include <arpa/inet.h>
#include "msg_ingame.hpp"	// hpp for the ones with classes

using namespace std;

// ANSWER
uint32_t AnswerMsg::bodySize() const { 
	return sizeof(uint32_t) + strlen(message); // strlen or just plain 900
}

void AnswerMsg::serializeBody(char * buffer) const {
	uint32_t conv_length = htonl(this->playerID);
	memcpy(buffer, &conv_length, sizeof(uint32_t));
	buffer += sizeof(uint32_t);

	strncpy(buffer, this->message, 900);
}

void AnswerMsg::deserializeBody(char * buffer) {
	uint32_t conv_length;
	memcpy(&conv_length, buffer, sizeof(uint32_t));
	playerID = ntohl(conv_length);
	buffer += sizeof(uint32_t);

	strncpy(this->message, buffer, 900);
}

string AnswerMsg::debugPrint() const {
	return to_string(this->playerID) 
		+ ":[" + string(this->message) + "]";
}