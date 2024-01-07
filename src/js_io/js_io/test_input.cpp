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
// 	x LOGIN,			AuthState::requestLogin(0, const char * name, const char * pass);
//	x REGISTER,			AuthState::requestLogin(1, const char * name, const char * pass);
// 	_ SUCCESS,			
// 	_ FAILURE,

// 	x JOIN_ROOM,		LobbyState::requestJoinRoom(int roomID);
// 	_ ROOM_LIST,		LobbyState::request
// 	x CREATE_ROOM,		LobbyState::request

// 	x CONNECT,			RoomState::requestDisconnect(int playerID);
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
		cout << "\033[96m RUN: " << query << "\033[0m" << endl;

		if (query == "login") {
			string name, pass;
			inputFile >> name >> pass;
			AuthState::requestLogin(0, name.c_str(), pass.c_str());
		} else if (query == "register") {
			string name, pass;
			inputFile >> name >> pass;
			AuthState::requestLogin(1, name.c_str(), pass.c_str());
		} else if (query == "getrooms") {
			LobbyState::requestGetRooms();
		} else if (query == "createroom") {
			inputFile >> input;
			LobbyState::requestCreateRoom(input.c_str());
		} else if (query == "joinroom") {
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

		} else if( query == "draw") {

			int x;
			int y;
			char color[7] ;
			int playerID;
			inputFile >> playerID >> x >> y >> color ;
			InGameState::requestDraw(playerID,x,y,color);
		}
		 else if( query == "start"){
			RoomState::requestStart();
		}
		else if( query == "answer" ){
			int playerID;
			char ans[900];
			inputFile >> playerID >> ans;
			InGameState::requestAnswer(playerID, ans);
			
		}
		else if( query == "score"){
			int score;
			int playerID;
			inputFile >> playerID >> score ;
			InGameState::requestScore(playerID , score);
		
		// } else if () {
		// } else if () {
		} else if (query == "pause!") {
			cout << "\r\033[96m   (Type anything) \033[0m" << endl;
				cin >> input; input = "";
		} 
		else {		
			if (query != "//") {	// Comments are skipped
				cout << "\r\033[96m COMMAND NOT FOUND: " << query << "\033[0m" << endl;		
			}

			inputFile.ignore(numeric_limits<streamsize>::max(), '\r');
		}
	}

	inputFile.close();
}

void globalJsEval(const std::string& js) { return; }	// Do nothing if test by cmd

