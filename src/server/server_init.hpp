#ifndef SERVER_INIT_H
#define SERVER_INIT_H

#include "server_lobby.hpp"	// All server handles

int initialize_server(int port);
void run_server(int sockfd);
void cleanup_server(int sockfd);

ServerLobby& get_server(int sockfd);


#endif