#ifndef LIB_PLAYERACC
#define LIB_PLAYERACC

#include <vector>

struct PlayerAccount {
	int playerID;
	char playerName[50];
	char password[50];
	int gamesPlayed;
	int gamesWin;
	int totalScore;
};

#endif