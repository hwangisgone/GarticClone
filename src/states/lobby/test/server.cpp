#include "network_const.h"
#include "server/server_init.hpp"

int main(){
	int server_sock; /* file descriptors */

	server_sock = initialize_server(CHOSEN_PORT);
	
	auto server1 = get_server(server_sock);
	

	cleanup_server(server_sock);
	
	return 0;
}