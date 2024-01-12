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

void fuckme() {
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
	w.set_size(500, 500, WEBVIEW_HINT_NONE);

	// Login
	w.bind("requestLogin", rqLogin, nullptr);

	// Register

	// Lobby
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

	// A binding that increments a value and immediately returns the new value.
	// w.bind("fuckaround", [&](const std::string & /*req*/) -> std::string {
	// 	auto count_string = std::to_string(++count);
	// 	return "{\"count\": " + count_string + "}";
	// });

	// // An binding that creates a new thread and returns the result at a later time.
	// w.bind(
	// 		"compute",
	// 		[&](const std::string &seq, const std::string &req, void * /*arg*/) {
	// 			// Create a thread and forget about it for the sake of simplicity.
	// 			std::thread([&, seq, req] {
	// 				// Simulate load.
	// 				// std::this_thread::sleep_for(std::chrono::seconds(1));
	// 				// json_parse() is an implementation detail and is only used here
	// 				// to provide a working example.
	// 				auto left = std::stoll(webview::detail::json_parse(req, "", 0));
	// 				auto right = std::stoll(webview::detail::json_parse(req, "", 1));
	// 				auto result = std::to_string(left * right);
	// 				w.resolve(seq, 0, result);
	// 			}).detach();
	// 		},
	// 		nullptr);

	w.set_html(html_const);
	
	std::thread clientThread(fuckme);

	w.run();

	clientThread.join();

	return 0;
}
