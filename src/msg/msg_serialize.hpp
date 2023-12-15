#ifndef MSG_SERIALIZE_H
#define MSG_SERIALIZE_H

#include <memory>

class BaseMsg;

#define BUFFER_SIZE 1024

class MsgBuffer {
private:
	char * currentPos;
	bool checkOverflow();
	void resetPointer();
public:
	char onceBuffer[BUFFER_SIZE + 1];

	void serializeMsg(const BaseMsg& msg);
	std::unique_ptr<BaseMsg> deserializeMsg();

	void serializeField(const uint32_t number);
	void serializeField(const uint16_t number);
	void serializeField(const char * str, const size_t len);

	void deserializeField(uint32_t * numberPtr);
	void deserializeField(uint16_t * numberPtr);
	void deserializeField(char * str, const size_t len);
};

#endif