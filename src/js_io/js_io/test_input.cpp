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
		// } else if () {
		// } else if () {
		// } else if () {
		// } else if () {			
		// } else if () {
		// } else if () {
		} else if (query == "pause!") {
			cout << "\033[96m   (Type anything) \033[0m" << endl;
				cin >> input; input = "";
		} 
		else if( query == "draw"){
			cout << "\033[96m RUN: " << query << "\033[0m" << endl;
			int x;
			int y;
			char color[7] ;
			int playerID;
			inputFile >> playerID >> x >> y >> color ;
			InGameState::requestDraw(playerID,x,y,color);
		}
		 else if( query == "start"){
			cout << "\033[96m RUN: " << query << "\033[0m" << endl;
			RoomState::requestStart();
		}
		else if( query == "answer" ){
			cout << "\033[96m RUN: " << query << "\033[0m" << endl;
			int playerID;
			char ans[900];
			inputFile >> playerID >> ans;
			InGameState::requestAnswer(playerID, ans);
			
		}
		else if( query == "score"){
			cout << "\033[96m RUN: " << query << "\033[0m" << endl;
			int score;
			int playerID;
			inputFile >> playerID >> score ;
			InGameState::requestScore(playerID , score);
		}
		// else if( query == "connect" ){
		// 	cout << "\033[96m RUN: ]" << query << "\033[0m" << endl;
		// 	int playerID;
		// 	InGameState:: requestConnect(playerID);
		// }
		// else if( query == "disconnect"){
		// 	cout << "\033[96m RUN: ]" << query << "\033[0m" << endl;
		// 	int playerID;
		// 	InGameState:: requestConnect(playerID);
		// }
		else {		
			if (query != "//") {	// Comments are skipped
				cout << "\033[96m COMMAND NOT FOUND: " << query << "\033[0m" << endl;		
			}

			inputFile.ignore(numeric_limits<streamsize>::max(), '\r');
		}
	}

	inputFile.close();
}

void globalJsEval(const std::string& js) { return; }	// Do nothing if test by cmd

