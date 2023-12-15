#include "network_const.h"
#include "client_init.hpp"

int main() {
	int client_sock;
	char addr[] = "127.0.0.1";

	client_sock = initialize_client(CHOSEN_PORT, addr);
	run_client(client_sock);
	cleanup_client(client_sock);

	return 0;
}