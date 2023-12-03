#include "server_handler.hpp"

void ServerHandler::run() {
	while (keepAlive) {
		currentState->handle();
	}
}

void ServerHandler::kill() {
	keepAlive = false;
}