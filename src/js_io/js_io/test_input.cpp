#include <fstream>
#include <string>
#include <limits>

#include <client/client_init.hpp>
#include "test_input.hpp"
#include "js_output.hpp"

using namespace std;

void run_test_input(const string& filePath) {
	ifstream inputFile(filePath);

	if (!inputFile.is_open()) {
		cerr << "Error opening the file." << endl;
		return;
	}

// TODO:
// 	_ AUTH,				AuthState::requestLogin(char type, const char * name, const char * pass);
// 	_ SUCCESS,			
// 	_ FAILURE,

// 	_ JOIN_ROOM,		LobbyState::requestJoinRoom(int roomID);
// 	_ ROOM_LIST,		
// 	_ CREATE_ROOM,

// 	_ CONNECT,			RoomState::requestDisconnect(int playerID);
// 	_ DISCONNECT,

// 	_ START_GAME,
// 	_ END_GAME,
// 	_ NEXT_ROUND,
// 	_ DRAW,
// 	_ ANSWER,
// 	_ SCORE,

	string query;
	string input = "";
	while(inputFile >> query) {
		if (query == "login") {
			cout << "\033[96m RUN: " << query << "\033[0m" << endl;
			string name, pass;
			inputFile >> name >> pass;
			AuthState::requestLogin(1, name.c_str(), pass.c_str());
		} else if (query == "register") {
			cout << "\033[96m RUN: " << query << "\033[0m" << endl;
			string name, pass;
			inputFile >> name >> pass;
			AuthState::requestLogin(0, name.c_str(), pass.c_str());
		} else if (query == "createroom") {
			cout << "\033[96m RUN: " << query << "\033[0m" << endl;
			inputFile >> input;
			LobbyState::requestCreateRoom(input.c_str());
		} else if (query == "joinroom") {
			cout << "\033[96m RUN: " << query << "\033[0m" << endl;
			int roomID;
			inputFile >> roomID;
			LobbyState::requestJoinRoom(roomID);		
		} else if (query == "exitroom") {
			RoomState::requestDisconnect();
		// } else if () {
		// } else if () {
		// } else if () {			
		// } else if () {
		// } else if () {
		} else if (query == "pause!") {
			cout << "\033[96m   (Type anything) \033[0m";
				cin >> input; input = "";
		} else {		
			if (query != "//") {	// Comments are skipped
				cout << "\033[96m COMMAND NOT FOUND: " << query << "\033[0m" << endl;		
			}

			inputFile.ignore(numeric_limits<streamsize>::max(), '\r');
		}
	}

	inputFile.close();
}

void globalJsEval(const std::string& js) { return; }	// Do nothing if test by cmd