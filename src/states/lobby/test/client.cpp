#include <iostream>
#include <thread>

#include <sys/socket.h>
#include <arpa/inet.h>

#include "network_const.h"
#include "client_init.hpp"

using namespace std;

unique_ptr<BaseMsg> inputToMsg() {
	return nullptr;
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