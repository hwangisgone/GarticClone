#ifndef MSG_SERIALIZE_H
#define MSG_SERIALIZE_H

void serializeMsg(char * buffer, const BaseMsg& msg);
std::unique_ptr<BaseMsg> deserializeMsg(char * buffer);

#endif