#ifndef CLIENT_AUTH_H
#define CLIENT_AUTH_H

#include "client/client_handler.hpp"


// Concrete States
class AuthState: public ClientState {
public:
	void handleRecv(const BaseMsg& msg) override;
	AuthState(): ClientState() {}
	// void requestLogin();
};

#endif