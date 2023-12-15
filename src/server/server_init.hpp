#ifndef SERVER_INIT_H
#define SERVER_INIT_H

int initialize_server(int port);
void run_server(int sockfd);
void cleanup_server(int sockfd);

#endif