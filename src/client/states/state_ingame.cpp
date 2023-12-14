#include <iostream>
#include <cstring>


#include "msg/types/msg_connect.hpp"
#include "msg/types/msg_ingame.hpp"

#include "debugging.h"

#include "client_handler.hpp"

using namespace std;


void InGameState::handleRecv(const BaseMsg &msg)
{
	DEBUG_PRINT("  (InGameState) " + msg.toString());

	switch (msg.type())
	{
	default:
		cerr << "CLIENT INGAME: MSG TYPE NOT INFERABLE: " << msg.toString() << endl;
	}
}