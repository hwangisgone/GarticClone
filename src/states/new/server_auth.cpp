#include <string>

#include "server_auth.hpp"
#include "textdatabase.hpp"

PlayerAccount * authenticate(AuthMsg& authmsg) {
	if(authmsg.auth_type == 0) {
		// Register
		DEBUG_PRINT("Registering new account: " + std::string(authmsg.username) + " - " + std::string(authmsg.password));
		return nullptr;
	} else {
		// Login
		DEBUG_PRINT("Login into: " + std::string(authmsg.username) + " - " + std::string(authmsg.password));
		return checkPassword(authmsg.username, authmsg.password);
	}
}