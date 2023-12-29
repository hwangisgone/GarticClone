#include "client/client_init.hpp"
#include "test_input.hpp"
#include "js_output.hpp"

using namespace std;

void globalJsEval(const std::string& js) { return; }	// Do nothing if test by cmd

void lobbyInput() {
	int roomid;
	cin >> roomid;
	
	LobbyState::requestJoinRoom(roomid);
}

void authInput() {
	char logintype = 0;
	string username, password;

	cout << "( reg | login ) ?\n";
	cin >> username;
	if (username == "reg") {
		logintype = 0;
	} else {
		logintype = 1;
	}

	// TODO: limit length in the UI
	cout << "Username: "; cin >> username;
	while (username.length() >= 50) {
		cout << "Username (<50 characters):";
		cin >> username;
	}

	cout << "Password: "; cin >> password;
	while (password.length() >= 100) {
		cout << "Password (<100 characters):";
		cin >> password;
	}

	AuthState::requestLogin(logintype, username.c_str(), password.c_str());
}