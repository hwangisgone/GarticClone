#ifndef CLIENT_CONN_H
#define CLIENT_CONN_H

#include "msg/msg_connection.hpp"
#include <client/client_handler.hpp>

namespace ClientConn 
{
	void handleConnect(const PlayerConnectMsg& msg, ClientHandler * client);
	void handleDisconnect(const PlayerDisconnectMsg& msg, ClientHandler * client);
	void backToRoom(ClientHandler * client);
}

#endif