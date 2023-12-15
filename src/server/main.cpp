#include "network_const.h"
#include "server_init.hpp"

int main(){
	int server_sock; /* file descriptors */

	server_sock = initialize_server(CHOSEN_PORT);
	run_server(server_sock);
	cleanup_server(server_sock);
	
	return 0;
}