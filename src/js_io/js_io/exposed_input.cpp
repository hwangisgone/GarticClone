#include "exposed_input.hpp"

#include <client/client_handler.hpp>

using namespace std;

#include <webview.h>
#include <iostream>

// Wrapper
void rqLogin(const string &seq, const string &req, void * /*arg*/) {
	auto type = stoll(webview::detail::json_parse(req, "", 0));
	auto username = webview::detail::json_parse(req, "", 1);
	auto password = webview::detail::json_parse(req, "", 2);
	
	AuthState::requestLogin(type, username.c_str(), password.c_str());
}

void rqJoinRoom(const string &seq, const string &req, void * /*arg*/) {
	auto roomID = stoll(webview::detail::json_parse(req, "", 0));
	
	LobbyState::requestJoinRoom(roomID);
}

void rqCreateRoom(const string &seq, const string &req, void * /*arg*/) {
	auto roomName = webview::detail::json_parse(req, "", 0);
	
	LobbyState::requestCreateRoom(roomName.c_str());
}

// In Game
void rqDraw(const std::string &seq, const std::string &req, void * /*arg*/) {
	auto x = stoll(webview::detail::json_parse(req, "", 0));
	auto y = stoll(webview::detail::json_parse(req, "", 1));
	auto clr = webview::detail::json_parse(req, "", 2);
	auto size = stoll(webview::detail::json_parse(req, "", 3));
	auto start = stoll(webview::detail::json_parse(req, "", 4));
	
		std::cerr << "Drawcalled\n";

	InGameState::requestDraw(x, y, clr.c_str(), size, start);
}

void rqAnswer(const std::string &seq, const std::string &req, void * /*arg*/) {
	auto answer = webview::detail::json_parse(req, "", 0);

	InGameState::requestAnswer(answer.c_str());
}


// Only proxy
void rqLogout(const string &seq, const string &req, void * /*arg*/) {
	AuthState::requestLogout();
}
void rqGetRooms(const string &seq, const string &req, void * /*arg*/) {
	LobbyState::requestGetRooms();
}
void rqDisconnect(const string &seq, const string &req, void * /*arg*/) {
	RoomState::requestDisconnect();
}
void rqStart(const string &seq, const string &req, void * /*arg*/) {
	RoomState::requestStart();
}
void rqGetLeaderboard(const string &seq, const string &req, void * /*arg*/) {
	LeaderboardState::requestGetLeaderboard();
}
void rqBackToRoom(const string &seq, const string &req, void * /*arg*/) {
	LeaderboardState::requestBackToRoom();
}






