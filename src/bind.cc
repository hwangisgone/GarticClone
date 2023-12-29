#include "webview.h"

#include <chrono>
#include <string>
#include <thread>
#include <iostream>

#include "network_const.h"
#include "client/client_init.hpp"	// Client

#include "in_out/exposed_input.hpp"	// Binding

extern const char* html_const;

webview::webview * globalw;

void fuckme() {
	int client_sock;
	char addr[] = "127.0.0.1";

	client_sock = initialize_client(CHOSEN_PORT, addr);

	auto client1 = get_client(client_sock);

	client1->setState(new AuthState());
	client1->run();

	cleanup_client(client_sock);
}

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE /*hInst*/, HINSTANCE /*hPrevInst*/,
									 LPSTR /*lpCmdLine*/, int /*nCmdShow*/) {
#else
int main() {
#endif
	unsigned int count = 0;
	webview::webview w(false, nullptr);
	globalw = &w;
	w.set_title("Charade.io");
	w.set_size(480, 320, WEBVIEW_HINT_NONE);

	w.bind("requestLogin", rqLogin, nullptr);

	w.bind("requestJoinRoom", rqJoinRoom, nullptr);

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
