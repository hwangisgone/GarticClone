#include "server_handler.hpp"

void DestroyState::handle() {
	serverHandler->kill();
}