#ifndef GAME_FORMAT_H
#define GAME_FORMAT_H

#include <unordered_map>
#include <sys/socket.h>
#include "sockaddr_in/sockaddr_in_functions.h"

enum GameState {
	LOBBY,
	ROOM,
	INGAME,
	LEADERBOARD,
	ENDSERVER,
};

struct Player {
	int score;
};

struct RoomInfo {
	sockaddr_in host;
	GameState currentState;
	std::unordered_map<sockaddr_in, Player, sockaddr_in_hash, sockaddr_in_equal> playerMap;
};

#endif