#ifndef EXPOSED_H
#define EXPOSED_H

#include <string>

void rqLogin(const std::string &seq, const std::string &req, void * /*arg*/);
void rqGetRooms(const std::string &seq, const std::string &req, void * /*arg*/);
void rqJoinRoom(const std::string &seq, const std::string &req, void * /*arg*/);
void rqCreateRoom(const std::string &seq, const std::string &req, void * /*arg*/);
void rqDisconnect(const std::string &seq, const std::string &req, void * /*arg*/);

#endif