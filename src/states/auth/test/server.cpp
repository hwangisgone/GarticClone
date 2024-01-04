#include <consts/network_const.h>
#include <server/server_init.hpp>

int main(){
	int server_sock; /* file descriptors */

	server_sock = initialize_server(CHOSEN_PORT);
	if (server_sock < 0) return 0;
	
	auto server1 = get_server(server_sock);
	server1->run();

	cleanup_server(server_sock);
	
	return 0;
}