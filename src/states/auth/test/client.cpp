#include <iostream>

#include <consts/network_const.h>

#include <client/client_init.hpp>
#include <js_io/test_input.hpp>

using namespace std;

int inputThread() {
	run_test_input("input.test.txt");

	string input; 
	cout << "Input? ( auth )" << endl;
	cin >> input;

	if (input == "auth") {
		authInput();
		return 0;
	} else {
		DEBUG_PRINT("Exiting");
		return -1;
	}
}

int main() {
	int client_sock;
	char addrstr[] = "127.0.0.1";

	// string addrstr = resolve_host(funnyaddress);
	// if (addrstr.empty()) return 0;
	// string addrstr ="127.0.0.1";

	client_sock = initialize_client(CHOSEN_PORT, addrstr);

	auto client1 = get_client(client_sock);

	client1->setState(new AuthState());

	client1->initialize_input_thread(inputThread);
	client1->run();
	client1->join_input_thread();

	cleanup_client(client_sock);

	return 0;
}