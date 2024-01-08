#ifndef ROOM_CONN_H
#define ROOM_CONN_H

#include "msg/msg_connection.hpp"
#include <lobby/msg/msg_lobby.hpp>
#include <server/room_handler.hpp>

namespace RoomConn 
{
	void handleConnect(const JoinRoomMsg& msg, int playerID, RoomHandler * room);
	void handleDisconnect(int playerID, RoomHandler * room);
}

#endif