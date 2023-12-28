#ifndef CLIENT_INIT_H
#define CLIENT_INIT_H

#include "client_handler.hpp"

int initialize_client(int port, char * inputAddr);
void run_client_from_state(int client_sock, ClientState * state);
void run_client(int client_sock);
void cleanup_client(int sockfd);

std::unique_ptr<ClientHandler> get_client(int client_sock);

#endif
