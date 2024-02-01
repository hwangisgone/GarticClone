#include "webview.h"

#include <iostream>
#include <chrono>
#include <string>
#include <thread>
#include <iostream>

#include <consts/network_const.h>
#include <client/client_init.hpp>	// Client

#include <js_io/exposed_input.hpp>	// Binding

extern const char* html_const;

webview::webview * globalw;

std::string chosenaddr = "127.0.0.1";

void client_running_thread() {
	int client_sock;
	// char funnyaddress[] = "charade.io.crabdance.com";

	// std::string addrstr = resolve_host(funnyaddress);
	// if (addrstr.empty()) return;
	std::cerr << chosenaddr << std::endl;

	client_sock = initialize_client(CHOSEN_PORT, chosenaddr.c_str());

	auto client1 = get_client(client_sock);

	client1->setState(new AuthState());
	client1->run();

	cleanup_client(client_sock);
}

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE /*hInst*/, HINSTANCE /*hPrevInst*/,
									 LPSTR /*lpCmdLine*/, int /*nCmdShow*/) {
#else
int main(int argc, char* argv[]) {
#endif
	if (argc == 2) {
		chosenaddr = argv[1];
	}

	unsigned int count = 0;
	webview::webview w(false, nullptr);
	globalw = &w;
	w.set_title("Charade.io");
	w.set_size(1040, 800, WEBVIEW_HINT_NONE);

	// Login
	// Register
	w.bind("requestLogin", rqLogin, nullptr);

	// Lobby
	w.bind("requestLogout", rqLogout, nullptr);

	w.bind("requestGetRooms", rqGetRooms, nullptr);
	w.bind("requestJoinRoom", rqJoinRoom, nullptr);
	w.bind("requestCreateRoom", rqCreateRoom, nullptr);

	// Room
	w.bind("requestDisconnect", rqDisconnect, nullptr);
	w.bind("requestStart", rqStart, nullptr);

	// InGame
	w.bind("requestDraw", rqDraw, nullptr);
	w.bind("requestAnswer", rqAnswer, nullptr);

	// Leaderboard
	w.bind("requestGetLeaderboard", rqGetLeaderboard, nullptr);
	w.bind("requestBackToRoom", rqBackToRoom, nullptr);

	w.set_html(html_const);
	
	std::thread clientThread(client_running_thread);

	w.run();

	clientThread.join();

	return 0;
}
