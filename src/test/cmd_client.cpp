#include <iostream>

#include <consts/network_const.h>

#include <client/client_init.hpp>
#include <js_io/test_input.hpp>
#include <printdebug/debugging.h>

using namespace std;

string clienttag = "";
string clientfolder = "";

int inputThread() {
	run_test_input("txt/" + clientfolder + "/input" + clienttag + ".test.txt");
	return -1;
}

int main(int argc, char* argv[]) {
	if (argc > 1) {
		if (argv[1][0] != '.') {
			clienttag = argv[1];
		}
	}

	if (argc > 2) {
		clientfolder = argv[2];
	}

	int client_sock;
	char addrstr[] = "127.0.0.1";

	// string addrstr = resolve_host(funnyaddress);
	// if (addrstr.empty()) return 0;
	// string addrstr ="127.0.0.1";
	load_test_file("txt/" + clientfolder + "/client" + clienttag + ".test.txt");
	TEST_PRINT("START");

	client_sock = initialize_client(CHOSEN_PORT, addrstr);

	auto client1 = get_client(client_sock);

	client1->setState(new AuthState());

	client1->initialize_input_thread(inputThread);
	client1->run();
	client1->join_input_thread();

	cleanup_client(client_sock);

	TEST_PRINT("END");
	TEST_PRINT("?");	// Last message to trigger the calculation of test

	return 0;
}