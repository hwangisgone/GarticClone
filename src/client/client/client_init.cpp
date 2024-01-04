#include <iostream>

#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>		// close

#include "client_init.hpp"

sockaddr_in serverAddress{};

std::string resolve_host(const char * hostname) {
	struct addrinfo *result, *rp;

	int err = getaddrinfo(hostname, NULL, NULL, &result);
	if (err != 0) {
		std::cerr << "getaddrinfo: " << gai_strerror(err) << std::endl;
		return "";
	}

	std::string ipstring;

	// Iterate through the list of addresses and use the first valid one
	for (rp = result; rp != nullptr; rp = rp->ai_next) {
		struct sockaddr_in *addr = (struct sockaddr_in *)rp->ai_addr;

		char ipstr[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &(addr->sin_addr), ipstr, INET_ADDRSTRLEN);

		ipstring = std::string(ipstr);
		std::cout << "Resolved IP address: " << ipstring << std::endl;
		break;
	}

	freeaddrinfo(result); // Free the memory allocated by getaddrinfo
	return ipstring;
}

int initialize_client(int port, const char * inputAddr) {
	// 1. Create a UDP socket
	int clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if (clientSocket == -1) {
		std::cerr << "Error creating socket" << std::endl;
		return -1;
	}

	// LINUX set RECV timeout
	struct timeval tv;
	tv.tv_sec = 3;
	tv.tv_usec = 0;
	setsockopt(clientSocket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);

	// 2.? Initialize serverAddress
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = inet_addr(inputAddr); // htonl(INADDR_ANY)??  /* INADDR_ANY puts your IP address automatically */
	serverAddress.sin_port = htons(port);

	std::cout << "Client initialized at " << std::string(inputAddr) << ":" << std::to_string(port) << std::endl;

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

std::unique_ptr<ClientHandler> get_client(int client_sock) {
	return std::make_unique<ClientHandler>(client_sock, serverAddress);
}