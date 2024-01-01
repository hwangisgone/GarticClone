#include <iostream>
#include <cstdio>		// memset
#include <cstdint>		// uint16, 32
#include <cstring>		// memcpy

#include <arpa/inet.h>

#include <type_traits>	// underlying_type

#include "msg_serialize.hpp"
#include "msg_format.hpp"

void MsgBuffer::resetPointer() {
	currentPos = onceBuffer;
}

bool MsgBuffer::checkOverflow() {
	if (currentPos > onceBuffer + BUFFER_SIZE || currentPos < onceBuffer) {
		std::cerr << "((de)serialize) STOP ADDING FIELDS: BUFFER OVERFLOW" << std::endl;
		return true;
	}
	return false;
}	

// serialize uint32_t
uint32_t byte4_conv;

void MsgBuffer::serializeField(const uint32_t number) {
	checkOverflow();
	byte4_conv = htonl(number);
	memcpy(currentPos, &byte4_conv, sizeof(uint32_t));
	currentPos += sizeof(uint32_t);
	return;
}

void MsgBuffer::deserializeField(uint32_t * numberPtr) {
	checkOverflow();
	if (numberPtr == nullptr) {
		std::cerr << "(uint32_t) WHAT ARE YOU DOING???: DESERIALIZE A NULL PTR???" << std::endl;
		return;
	}
	memcpy(&byte4_conv, currentPos, sizeof(uint32_t));
	*numberPtr = ntohl(byte4_conv);
	currentPos += sizeof(uint32_t);
	return;
}

// TODO: implement this?
uint32_t byte2_conv;

void MsgBuffer::serializeField(const uint16_t number) {
	checkOverflow();
	currentPos += sizeof(uint16_t);
}
void MsgBuffer::deserializeField(uint16_t * numberPtr) {
	checkOverflow();
	if (numberPtr == nullptr) {
		std::cerr << "(uint16_t) WHAT ARE YOU DOING???: DESERIALIZE A NULL PTR ???" << std::endl;
		return;
	}
	currentPos += sizeof(uint16_t);
}


void MsgBuffer::serializeField(const char * str, const size_t len) {
	checkOverflow();
	strncpy(currentPos, str, len);
	currentPos += len;
}

void MsgBuffer::deserializeField(char * str, const size_t len) {
	checkOverflow();
	if (str == nullptr) {
		std::cerr << "(str) WHAT ARE YOU DOING???: DESERIALIZE A NULL PTR???" << std::endl;
		return;
	}

	strncpy(str, currentPos, len);
	currentPos += len;
}

void MsgBuffer::serializeMsg(const BaseMsg& msg) {
	// Clear onceBuffer and serializing
	memset(onceBuffer, 0, sizeof(onceBuffer));

	resetPointer();
	uint16_t conv_type = htons(static_cast<std::underlying_type<MsgType>::type>(msg.type()));						// Host short to Network short
	uint32_t conv_length = htonl(msg.length());	// Host long to Network long

	// Type: 2 bytes
	memcpy(currentPos, &conv_type, sizeof(uint16_t));
	currentPos += sizeof(uint16_t); // Move buffer pointer

	// Length: 4 bytes
	memcpy(currentPos, &conv_length, sizeof(uint32_t));
	currentPos += sizeof(uint32_t); // Move buffer pointer

	msg.serializeBody(*this);
}

std::unique_ptr<BaseMsg> MsgBuffer::deserializeMsg() {
	resetPointer();
	uint16_t conv_type;
	uint32_t conv_length;

	// Type: 2 bytes
	memcpy(&conv_type, currentPos, sizeof(uint16_t));	
	currentPos += sizeof(uint16_t); // Move buffer pointer

	// Length: 4 bytes
	memcpy(&conv_length, currentPos, sizeof(uint32_t));
	currentPos += sizeof(uint32_t);

	MsgType current_type = static_cast<MsgType>(ntohs(conv_type));
	std::unique_ptr<BaseMsg> msg = factoryProduceMsg(current_type);

	if (!msg) {
		std::cerr << "Deserialize: Type unrecognized, cannot deserialize: " << conv_type << std::endl;
		return nullptr;
	}

	// Convert int back Network -> Host
	msg->setLength(ntohl(conv_length));
	msg->deserializeBody(*this);
	return msg;
}