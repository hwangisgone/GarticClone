#include <consts/network_const.h>
#include <server/server_init.hpp>

#include <printdebug/debugging.h>

int main(){
	int server_sock; /* file descriptors */

	load_test_file("txt/server.test.txt");
	TEST_PRINT("START");

	server_sock = initialize_server(CHOSEN_PORT);
	if (server_sock < 0) return 0;
	
	auto server1 = get_server(server_sock);
	server1->run();

	cleanup_server(server_sock);

	TEST_PRINT("END");
	TEST_PRINT("?");	// Last message to trigger the calculation of test

	return 0;
}