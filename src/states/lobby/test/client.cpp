#include <iostream>
#include <thread>

#include <sys/socket.h>
#include <arpa/inet.h>

#include "network_const.h"
#include "client_init.hpp"
#include "client_input.hpp"


using namespace std;

unique_ptr<BaseMsg> inputToMsg() {

}

void sendInput(int sockfd, const sockaddr_in * serverAddrPtr) {
	sendMsg(sockfd, serverAddrPtr, )
}

int main() {
	int client_sock;
	char addr[] = "127.0.0.1";

	thread inputThread = thread()

	client_sock = initialize_client(CHOSEN_PORT, addr);
	initialize_input_thread(inputToMsg);

	run_client_from_state(client_sock, new LobbyState());

	cleanup_thread();
	cleanup_client(client_sock);

	return 0;
}