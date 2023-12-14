#include <iostream>
#include <cstdio>		// memset
#include <cstdint>		// uint16, 32
#include <cstring>		// memcpy

#include <arpa/inet.h>

#include <type_traits>	// underlying_type

#include "msg_format.hpp"

void serializeMsg(char * buffer, const BaseMsg& msg) {
	uint16_t conv_type = htons(static_cast<std::underlying_type<MsgType>::type>(msg.type()));						// Host short to Network short
	uint32_t conv_length = htonl(msg.length());	// Host long to Network long

	// Type: 2 bytes
	memcpy(buffer, &conv_type, sizeof(uint16_t));
	buffer += sizeof(uint16_t); // Move buffer pointer

	// Length: 4 bytes
	memcpy(buffer, &conv_length, sizeof(uint32_t));
	buffer += sizeof(uint32_t); // Move buffer pointer

	msg.serializeBody(buffer);
}

std::unique_ptr<BaseMsg> deserializeMsg(char * buffer) {
	uint16_t conv_type;
	uint32_t conv_length;

	// Type: 2 bytes
	memcpy(&conv_type, buffer, sizeof(uint16_t));	
	buffer += sizeof(uint16_t); // Move buffer pointer

	// Length: 4 bytes
	memcpy(&conv_length, buffer, sizeof(uint32_t));
	buffer += sizeof(uint32_t);

	MsgType current_type = static_cast<MsgType>(ntohs(conv_type));
	std::unique_ptr<BaseMsg> msg = factoryProduceMsg(current_type);

	if (!msg) {
		std::cerr << "Deserialize: Type unrecognized, cannot deserialize: " << conv_type << std::endl;
		return nullptr;
	}

	// Convert int back Network -> Host
	msg->setLength(ntohl(conv_length));
	msg->deserializeBody(buffer);
	return msg;
}