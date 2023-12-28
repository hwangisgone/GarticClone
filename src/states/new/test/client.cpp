#include <iostream>
#include <thread>

#include <sys/socket.h>
#include <arpa/inet.h>

#include "network_const.h"
#include "client/client_init.hpp"

#include "states/new/msg_auth.hpp"

using namespace std;

int inputThread() {
	string input, username, password;
	char auth_type = 0;
	cout << "Input? (reg | login)" << endl;
	cin >> input;

	if (input == "reg" || input == "login") {
		if (input == "reg") {
			auth_type = 0;
		} else {
			auth_type = 1;
		}

		// TODO: limit it in the UI
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

		AuthState::requestLogin(auth_type, username.c_str(), password.c_str());

		return 0;
	} else {
		DEBUG_PRINT("Exiting");
		return -1;
	}
}

int main() {
	int client_sock;
	char addr[] = "127.0.0.1";

	client_sock = initialize_client(CHOSEN_PORT, addr);

	auto client1 = get_client(client_sock);

	client1->setState(new AuthState());

	client1->initialize_input_thread(inputThread);
	client1->run();
	client1->join_input_thread();

	cleanup_client(client_sock);

	return 0;
}