#ifndef DB_HHH
#define DB_HHH

struct PlayerAccount {
	int playerID;
	int multiGameScore;
	char playerName[50];
};

std::unordered_map<int, PlayerAccount> allAccounts;
int accountCount = 0;


#endif