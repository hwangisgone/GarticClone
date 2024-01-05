#ifndef DB_HHH
#define DB_HHH

#include <unordered_map>
#include <string>
#include <types/playeraccount.hpp>

extern std::vector<PlayerAccount> allAccounts;
extern int accountCount;

bool loadFromFile(const std::string& filename, std::vector<PlayerAccount>& accounts);

void writeWordsToFile(const std::string& filename, const std::vector<PlayerAccount>& accounts);

std::vector<PlayerAccount>::iterator findPlayer(std::vector<PlayerAccount> &accounts, int playerID);

int addAccount(const char * in_username, const char * in_password);
PlayerAccount * checkPassword(const char * username, const char * password);

void updatePlayer(std::vector<PlayerAccount> &accounts, int playerID, int plusScore, bool win);

#endif