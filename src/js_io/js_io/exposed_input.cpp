#include "exposed_input.hpp"

#include <client/client_handler.hpp>

using namespace std;

#include <webview.h>

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


void rqDisconnect(const string &seq, const string &req, void * /*arg*/) {
	RoomState::requestDisconnect();
}

