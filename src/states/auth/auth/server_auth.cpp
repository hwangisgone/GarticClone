#include <string>

#include "server_auth.hpp"
#include <database/textdatabase.hpp>

PlayerAccount * authenticate(const LoginMsg& msg) {
	TEST_PRINT("Login into: " + std::string(msg.username) + " - " + std::string(msg.password));
	PlayerAccount * logged = checkPassword(msg.username, msg.password);
	if (logged == nullptr) {
		TEST_PRINT("> Incorrect credentials.");
	}
	return logged;
}

int registeraccount(const RegisterMsg& msg) {
	// Register
	TEST_PRINT("Registering new account: " + std::string(msg.username) + " - " + std::string(msg.password));
	int playerID = addAccount(msg.username, msg.password);
	if (playerID > 0) {
		TEST_PRINT("> Register success! Player #" + std::to_string(playerID));
	} else {
		TEST_PRINT("> Register fail.");
	}

	return playerID;
}