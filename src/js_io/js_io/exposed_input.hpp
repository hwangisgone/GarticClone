#ifndef EXPOSED_H
#define EXPOSED_H

#include <string>

void rqLogin(const std::string &seq, const std::string &req, void * /*arg*/);

void rqGetRooms(const std::string &seq, const std::string &req, void * /*arg*/);
void rqCreateRoom(const std::string &seq, const std::string &req, void * /*arg*/);
void rqJoinRoom(const std::string &seq, const std::string &req, void * /*arg*/);

void rqDisconnect(const std::string &seq, const std::string &req, void * /*arg*/);
void rqStart(const std::string &seq, const std::string &req, void * /*arg*/);

void rqDraw(const std::string &seq, const std::string &req, void * /*arg*/);
void rqAnswer(const std::string &seq, const std::string &req, void * /*arg*/);

void rqGetLeaderboard(const std::string &seq, const std::string &req, void * /*arg*/);
void rqBackToRoom(const std::string &seq, const std::string &req, void * /*arg*/);
#endif