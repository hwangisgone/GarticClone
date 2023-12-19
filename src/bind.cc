#include "webview.h"

#include <chrono>
#include <string>
#include <thread>
#include <iostream>

extern const char* html_const;

webview::webview * globalw;

void fuckmemore() {
	globalw->eval("increment()");
}

void fuckme() {
	std::this_thread::sleep_for(std::chrono::seconds(4));
	for (int i = 0; i < 10; ++i) {
		globalw->dispatch(fuckmemore);
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
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

	// A binding that increments a value and immediately returns the new value.
	w.bind("fuckaround", [&](const std::string & /*req*/) -> std::string {
		auto count_string = std::to_string(++count);
		return "{\"count\": " + count_string + "}";
	});

	// An binding that creates a new thread and returns the result at a later time.
	w.bind(
			"compute",
			[&](const std::string &seq, const std::string &req, void * /*arg*/) {
				// Create a thread and forget about it for the sake of simplicity.
				std::thread([&, seq, req] {
					// Simulate load.
					// std::this_thread::sleep_for(std::chrono::seconds(1));
					// json_parse() is an implementation detail and is only used here
					// to provide a working example.
					auto left = std::stoll(webview::detail::json_parse(req, "", 0));
					auto right = std::stoll(webview::detail::json_parse(req, "", 1));
					auto result = std::to_string(left * right);
					w.resolve(seq, 0, result);
				}).detach();
			},
			nullptr);

	w.set_html(html_const);
	std::thread fuck1(fuckme);

	w.run();

	fuck1.join();

	return 0;
}
