#include <iostream>
#include <thread>

#include <sys/socket.h>
#include <arpa/inet.h>

#include "network_const.h"
#include "client/client_init.hpp"

#include "states/new/msg_auth.hpp"
#include "states/lobby/msg_lobby.hpp"

using namespace std;

unique_ptr<BaseMsg> inputToMsg() {
	string input;
	cout << "Input? (auth | joinroom x | exit)" << endl;
	cin >> input;

	if (input == "auth") {
		auto msg = make_unique<AuthMsg>();
		return msg;
	} else if (input == "joinroom") {
		int roomid;
		cin >> roomid;
		auto msg = make_unique<JoinRoomMsg>();
		msg->roomID = roomid;
		return msg;
	} else {
		DEBUG_PRINT("Exiting");
		return nullptr;
	}
}

int main() {
	int client_sock;
	char addr[] = "127.0.0.1";

	client_sock = initialize_client(CHOSEN_PORT, addr);

	auto client1 = get_client(client_sock);

	client1.setState(new LobbyState());

	client1.initialize_input_thread(inputToMsg);
	client1.run();
	client1.join_input_thread();

	cleanup_client(client_sock);

	return 0;
}