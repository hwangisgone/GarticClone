#include <unordered_map>

#include <fstream>
#include <iostream>
#include <cstring>

#include "textdatabase.hpp"

// std::unordered_map<int, PlayerAccount> allAccounts;
int accountCount = 0;
std::vector<PlayerAccount> allAccounts;

// Function to load data from a text file into a vector of structs
bool loadFromFile(const std::string& filename, std::vector<PlayerAccount>& accounts)
{
	std::ifstream file(filename);

	if (!file.is_open())
	{
		std::cerr << "Error opening file: " << filename << std::endl;
		return false;
	}
	std::cerr << "Reading accounts from " + filename << std::endl;

	// Read data from each line in the file
	while (!file.eof())
	{
		PlayerAccount account;
		// Assuming the file format is: name age height
		file >> account.playerID >> account.playerName >> account.password >> account.gamesPlayed >> account.gamesWin >> account.totalScore;
		
		// Check for errors while reading
		if (file.fail())
		{
			break;  // Break if reading fails, assuming end of file or bad format
		}
		// Add the person to the vector
		accounts.push_back(account);
	}

	// Close the file
	file.close();
	return true;
}

void writePlayerAccountsToFile(const std::string& filename, const std::vector<PlayerAccount>& accounts)
{
	std::ofstream file(filename);

	if (!file.is_open())
	{
		std::cerr << "Error opening file: " << filename << std::endl;
		return;
	}

	// Write each PlayerAccount to the file
	for (const auto& account : accounts)
	{
		file << account.playerID << " " << account.playerName << " " << account.password << " " << account.gamesPlayed << " " << account.gamesWin << " " <<  account.totalScore;
	}

	// Close the file
	file.close();
}

std::vector<PlayerAccount>::iterator findPlayer(std::vector<PlayerAccount> &accounts, int playerID )
{
	for (auto it = accounts.begin(); it != accounts.end(); ++it)
	{
		if( it->playerID == playerID)
			return it;
	}
	return accounts.end(); // Word not found
}

PlayerAccount * checkPassword(const char * username, const char * password) {
	std::cerr << "Acc counts: " << allAccounts.size() << std::endl;
	for (auto& account : allAccounts) {
		if (strcmp(account.playerName, username) == 0) {
			// Username match found
			if(strcmp(account.password, password) == 0) {
				return &account;
			} else {
				return nullptr;
			}
		}
	}
	return nullptr;
}

int addAccount(const char * in_username, const char * in_password) {
	for (auto& account : allAccounts) {
		if (strcmp(account.playerName, in_username) == 0) {
			return -1;
		}
	}

	PlayerAccount account;
	account.playerID = allAccounts.size() + 1;
	strncpy(account.playerName, in_username, 50);
	strncpy(account.password, in_password, 50);
	account.gamesPlayed	= 0;
	account.gamesWin	= 0;
	account.totalScore	= 0;

	allAccounts.push_back(account);

	return account.playerID;
}

void updatePlayer(std::vector<PlayerAccount> &accounts, int playerID, int plusScore, bool win){
	auto player = findPlayer(accounts, playerID);

	player->totalScore += plusScore;
	player->gamesPlayed ++;
	if( win ){
		player->gamesWin ++;
	}
}
