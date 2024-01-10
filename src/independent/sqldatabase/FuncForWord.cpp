#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>    // std::tolower
#include <algorithm> // std::equal
#include <ctime>
#include <sqlite3.h>
//#include "word_list.hpp"

using namespace std;
/*
struct Word
{
	char word[50];
	int totalCount;
	int successCount;
	int level;
	//	0 easy
	//	1 medium
	//	2 hard
};
// Function to load data from a text file into a vector of structs
*/
bool loadFromFile(const char* s, std::vector<Word>&accounts) {
        sqlite3* DB;
        sqlite3_stmt* stmt;
        std::string sql1 = "SELECT * FROM Word";
        const char* sql = sql1.c_str();
        int exit = sqlite3_open(s, &DB);
        if (exit != SQLITE_OK) {
            std::cerr << "Error opening database: " << s << std::endl;
            return false;
        }
        else {
            std::cout << "Open database !\n";
        }
        exit = sqlite3_prepare_v2(DB, sql, -1, &stmt, NULL);
        while ((exit = sqlite3_step(stmt)) == SQLITE_ROW) {
            Word account;
           

            const char* word = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            
            strcpy_s(account.word, sizeof(account.word), word);

            account.totalCount = sqlite3_column_int(stmt, 1);
            account.successCount = sqlite3_column_int(stmt, 2);
            account.level = sqlite3_column_int(stmt, 3);
            std::cout << "Push: " << account.word << ", " << account.totalCount << ", " << account.successCount << ", " << account.level << "\n";
            accounts.push_back(account);
        }

        // Don't forget to finalize the statement
        sqlite3_finalize(stmt);

        return true; // Return the number of records retrieved
    }
void writeWordsToFile(const char* s, const std::vector<Word>& accounts)
{
    sqlite3* DB;
    char* messageError;

    int exit = sqlite3_open(s, &DB);
    if (exit != SQLITE_OK) {
        std::cerr << "Error opening database: " << s << std::endl;
        return;
    }
    for (int i = 0; i < accounts.size(); i++)
    {
        cout << accounts[i].word << ", " << accounts[i].totalCount << "\n";
    }

    std::string delete_sql = "DELETE FROM Word";
    int delete_res = sqlite3_exec(DB, delete_sql.c_str(), NULL, 0, &messageError);
    if (delete_res != SQLITE_OK) {
        std::cout << "Delete fail!\n";
    }
    else std::cout << "Delete successfully!\n";
    // Write each PlayerAccount to the DATABASE
    for (const auto& account : accounts)
    {
        std::string sql = "INSERT INTO Word(word, totalCount, successCount, level) VALUES( '" + std::string(account.word) + "'," + std::to_string(account.totalCount) + ", " + std::to_string(account.successCount) + ", " + std::to_string(account.level) + ")";
       // std::cout << sql << "\n";
        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
        if (exit != SQLITE_OK) {
            std::cerr << "Error when insert word: " << account.word << std::endl;
            return;

        }

    }

    sqlite3_close(DB);


    // Close the file

}
