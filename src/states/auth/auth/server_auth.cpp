#include <string>

#include "server_auth.hpp"
#include <database/textdatabase.hpp>

PlayerAccount * authenticate(AuthMsg& authmsg) {
	if(authmsg.auth_type == 0) {
		// Register
		TEST_PRINT("Registering new account: " + std::string(authmsg.username) + " - " + std::string(authmsg.password));
		int playerID = addAccount(authmsg.username, authmsg.password);
		if (playerID > 0) {
			TEST_PRINT("Register success! Player #" + std::to_string(playerID));
		} else {
			TEST_PRINT("Register fail.");
		}

		return nullptr;
	} else {
		// Login
		TEST_PRINT("Login into: " + std::string(authmsg.username) + " - " + std::string(authmsg.password));
		PlayerAccount * logged = checkPassword(authmsg.username, authmsg.password);
		if (logged == nullptr) {
			TEST_PRINT("Incorrect credentials.");
		}
		return logged;
	}
}