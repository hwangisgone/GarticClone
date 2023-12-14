#include <cstdint>
#include <cstring>

#include "msg_connect.hpp"	// hpp for the ones with classes

using namespace std;

// CONNECT 
uint32_t ConnectMsg::bodySize() const { 
	return sizeof(uint32_t); // 4 bytes
}

void ConnectMsg::serializeBody(char * buffer) const {
	uint32_t conv_length = htonl(playerID);
	memcpy(buffer, &conv_length, sizeof(uint32_t));
}

void ConnectMsg::deserializeBody(char * buffer) {
	uint32_t conv_length;
	memcpy(&conv_length, buffer, sizeof(uint32_t));
	playerID = ntohl(conv_length);
}

string ConnectMsg::debugPrint() const {
	return to_string(playerID);
}

// & DISCONNECT (They're the same)
uint32_t DisconnectMsg::bodySize() const { 
	return sizeof(uint32_t); // 4 bytes
}

void DisconnectMsg::serializeBody(char * buffer) const {
	uint32_t conv_length = htonl(playerID);
	memcpy(buffer, &conv_length, sizeof(uint32_t));
}

void DisconnectMsg::deserializeBody(char * buffer) {
	uint32_t conv_length;
	memcpy(&conv_length, buffer, sizeof(uint32_t));
	playerID = ntohl(conv_length);
}

string DisconnectMsg::debugPrint() const {
	return to_string(playerID);
}