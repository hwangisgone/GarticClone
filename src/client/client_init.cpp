#include <iostream>
#include <thread>

#include <arpa/inet.h>
#include <unistd.h>		// close

#include "client_handler.hpp"

sockaddr_in serverAddress{};

int initialize_client(int port, char * inputAddr) {
	// 1. Create a UDP socket
	int clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if (clientSocket == -1) {
		std::cerr << "Error creating socket" << std::endl;
		return -1;
	}

	// TODO: setsockopt TIMER for RECV

	// 2.? Initialize serverAddress
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = inet_addr(inputAddr); // htonl(INADDR_ANY)??  /* INADDR_ANY puts your IP address automatically */
	serverAddress.sin_port = htons(port);

	return clientSocket;
}

void cleanup_client(int sockfd) {
	close(sockfd);
}

void run_client_from_state(int client_sock, ClientState * state) {
	printf("Client started.\n");
	ClientHandler client1(client_sock, serverAddress);
	client1.setState(state);
	client1.run();
}

void run_client(int client_sock) {
	printf("Client started.\n");
	ClientHandler client1(client_sock, serverAddress);
	client1.run();
}


// MOVE THIS TO THE ClientHandler itself (using KeepAlive to kill both)
// For testing,
void sendInput(int sockfd, unique_ptr<BaseMsg> (*)() getInput) {
	while (true) {
		unique_ptr<BaseMsg> msg = getInput();
		sendMsg(sockfd, (struct sockaddr *)&serverAddress, sizeof(serverAddress), *msg)
	}
}

std::thread inputThread;
void initialize_input_thread() {
	inputThread = std::thread()
}