#ifndef DB_HHH
#define DB_HHH

#include <unordered_map>
#include <vector>
#include <string>

struct PlayerAccount {
	int playerID;
	char playerName[50];
	char password[50];
	int gamesPlayed;
	int gamesWin;
	int totalScore;
};

extern std::vector<PlayerAccount> allAccounts;
extern int accountCount;

bool loadFromFile(const std::string& filename, std::vector<PlayerAccount>& accounts);

void writeWordsToFile(const std::string& filename, const std::vector<PlayerAccount>& accounts);

std::vector<PlayerAccount>::iterator findPlayer(std::vector<PlayerAccount> &accounts, int playerID);

PlayerAccount * checkPassword(const char * username, const char * password);

void updatePlayer(std::vector<PlayerAccount> &accounts, int playerID, int plusScore, bool win);

#endif