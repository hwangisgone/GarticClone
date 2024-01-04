#include <string>

#include "server_auth.hpp"
#include <database/textdatabase.hpp>

PlayerAccount * authenticate(AuthMsg& authmsg) {
	if(authmsg.auth_type == 0) {
		// Register
		TEST_PRINT("Registering new account: " + std::string(authmsg.username) + " - " + std::string(authmsg.password));
		return nullptr;
	} else {
		// Login
		TEST_PRINT("Login into: " + std::string(authmsg.username) + " - " + std::string(authmsg.password));
		return checkPassword(authmsg.username, authmsg.password);
	}
}