#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

#include <thread>
#include <mutex>

#include "msg/msg_format.hpp"
#include "msg/msg_sendrecv.h"
#include "network_const.h"

std::mutex mtx;
bool exitProgram = false;

sockaddr_in serverAddress{};

int initialize_client(int port, char * inputAddr) {
	// 1. Create a UDP socket
	int clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if (clientSocket == -1) {
		std::cerr << "Error creating socket" << std::endl;
		return -1;
	}

	// 2.? Initialize serverAddress
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = inet_addr(inputAddr); // htonl(INADDR_ANY)??  /* INADDR_ANY puts your IP address automatically */
	serverAddress.sin_port = htons(port);

	return clientSocket;
}

void cleanup_client(int sockfd) {
	close(sockfd);
}

// void client_echo(int clientSocket) {
// 	//std::thread printing(getMsg, clientSocket);
// 	BaseMsg msg(MsgType::CONNECT);
// 	// Get user input and send messages to the server
// 	// while (true) {
// 		// Send the message to the server
// 	sendMsg(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress), msg);
// 	// while (true) {
		
// 	// }
// 	// }

// 	//printing.join();
// }

void client_echo(int clientSocket) {
	
}


void run_client(int client_sock) {
	printf("Client started.\n");
	client_echo(client_sock);
}


int main() {
	int client_sock;
	char addr[] = "127.0.0.1";

	client_sock = initialize_client(CHOSEN_PORT, addr);
	run_client(client_sock);
	cleanup_client(client_sock);

	return 0;
}