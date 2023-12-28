#ifndef DB_HHH
#define DB_HHH

#include <unordered_map>

struct PlayerAccount {
	int playerID;
	int multiGameScore;
	char playerName[50];
};

extern std::unordered_map<int, PlayerAccount> allAccounts;
extern int accountCount;


#endif