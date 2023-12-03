#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

#include <thread>
#include <mutex>

#include "network_const.h"

std::mutex mtx;
bool exitProgram = false;

void getMsg(int clientSocket) {
	char buffer[BUFFER_SIZE];
	AppMsg msg;
	while(true) {
		// Receive the response from the server

		ssize_t receivedBytes = recvfrom(clientSocket, buffer, BUFFER_SIZE, 0, nullptr, nullptr);
		if (receivedBytes == -1) {
			std::cerr << "Error receiving data" << std::endl;
			continue;
		}
		buffer[receivedBytes] = '\0';

		deserializeMsg(buffer, &msg);

		std::cout << "Received from server: ";
		printMsg(&msg);
		std::cout << std::endl;

		if ()

		{
			std::lock_guard<std::mutex> lock(mtx);
			if (exitProgram) {
				break;  // Exit the loop and end the thread
			}
		}   // The lock_guard automatically releases the lock when it goes out of scope
	}
}

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

void client_echo(int clientSocket, const sockaddr_in& serverAddress) {
	std::thread printing(getMsg, clientSocket);

	// Get user input and send messages to the server
	while (true) {
		std::cout << "Enter a message to send to the server (or type 'exit' to quit): ";
		std::string message;
		std::getline(std::cin, message);

		// Check if the user wants to exit
		if (message == "exit") {
			{
				std::lock_guard<std::mutex> lock(mtx);
				exitProgram = true;
			}
			break;
		}

		// Send the message to the server
		ssize_t sentBytes = sendto(clientSocket, message.c_str(), message.size(), 0, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
		if (sentBytes == -1) {
			std::cerr << "Error sending data" << std::endl;
			continue;
		}
	}

	printing.join();
}


void run_client(int client_sock) {
	printf("Client started.\n");
	client_echo(client_sock);
}


int main() {
	int client_sock;

	client_sock = initialize_client(CHOSEN_PORT, "127.0.0.1");
	run_client(client_sock);
	cleanup_client(client_sock);

	return 0;
}