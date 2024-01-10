#include <sqlite3.h>
#include <iostream>
#include <stdio.h>
#include <stdexcept>
#include <string>
#include <cstring>
#include <string.h>
#include <stdlib.h>
#include <unordered_map>


using namespace std;

int accountCount = 0;
std::vector<PlayerAccount> allAccounts;
char* encodePass(const char* mes) {
    char* encode = (char*)malloc(strlen(mes) + 1);
    for (int i = 0; i < strlen(mes); i++) {
        encode[i] = mes[i] + (i + 1) * (i + 1) % 128;
        



    }
    encode[strlen(mes)] = '\0';
    return encode;
}


bool loadFromFile(const char* s, std::vector<PlayerAccount>& accounts) {
    sqlite3* DB;
    sqlite3_stmt* stmt;
    std::string sql1 = "SELECT * FROM Players";
    const char* sql = sql1.c_str();
    int exit = sqlite3_open(s, &DB);
    if (exit != SQLITE_OK) {
        std::cerr << "Error opening database: " << s << std::endl;
        return false;
    }
    exit = sqlite3_prepare_v2(DB, sql, -1, &stmt, NULL);
    while ((exit = sqlite3_step(stmt)) == SQLITE_ROW) {
        PlayerAccount account;
        account.playerID = sqlite3_column_int(stmt, 0);

        const char* username = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        const char* password = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        strcpy_s(account.playerName, sizeof(account.playerName), username);
        strcpy_s(account.password, sizeof(account.password), password);

        account.gamesPlayed = sqlite3_column_int(stmt, 3);
        account.gamesWin = sqlite3_column_int(stmt, 4);
        account.totalScore = sqlite3_column_int(stmt, 5);
        accounts.push_back(account);
    }

    // Don't forget to finalize the statement
    sqlite3_finalize(stmt);

    return true; // Return the number of records retrieved
}
PlayerAccount* findPlayer(const char* s, std::vector<PlayerAccount>& accounts, int playerID)
{
    sqlite3* DB;
    sqlite3_stmt* stmt;

    // Opening the database
    int exit = sqlite3_open(s, &DB);
    if (exit != SQLITE_OK) {
        std::cerr << "Error opening database: " << s << std::endl;
        return nullptr; // Returning accounts.end() since the database couldn't be opened
    }

    std::string find_sql = "SELECT * FROM Players WHERE playerID = " + std::to_string(playerID);

    // Preparing the SQL statement
    exit = sqlite3_prepare_v2(DB, find_sql.c_str(), -1, &stmt, 0);

    // Checking for errors in preparing the statement
    if (exit != SQLITE_OK) {
        std::cerr << "Error preparing SQL statement: " << sqlite3_errmsg(DB) << std::endl;
        sqlite3_close(DB);
        return nullptr;
    }

    // Executing the SQL statement
    exit = sqlite3_step(stmt);
    if (exit == SQLITE_ROW) {
        PlayerAccount account;

        // Retrieving data from the result set
        account.playerID = sqlite3_column_int(stmt, 0);
        const char* username = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        const char* password = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        strcpy_s(account.playerName, sizeof(account.playerName), username);
        strcpy_s(account.password, sizeof(account.password), password);
        account.gamesPlayed = sqlite3_column_int(stmt, 3);
        account.gamesWin = sqlite3_column_int(stmt, 4);
        account.totalScore = sqlite3_column_int(stmt, 5);

        std::cout << "Information:" << account.playerID << ", " << account.playerName << ", " << account.password << ", " << account.gamesPlayed << ", " << account.gamesWin << ", " << account.totalScore;
        // Closing the statement and database
        sqlite3_finalize(stmt);
        sqlite3_close(DB);

        // Returning the found account
        return &account;
    }
    std::cout << "Find FAIL";
    // Finalizing the statement and closing the database
    sqlite3_finalize(stmt);
    sqlite3_close(DB);

    // Returning accounts.end() since the player with the specified ID was not found
    return nullptr;
}

PlayerAccount* checkPassword(const char* s, const char* username, const char* password) {
    password = encodePass(password);
    sqlite3* DB;
    sqlite3_stmt* stmt;

    // Opening the database
    int exit = sqlite3_open(s, &DB);
    if (exit != SQLITE_OK) {
        std::cerr << "Error opening database: " << s << std::endl;
        return nullptr; // Returning accounts.end() since the database couldn't be opened
    }

    std::string find_sql = "SELECT * FROM Players WHERE username = '" + std::string(username) + "' AND password = '" + std::string(password) + "'";

    exit = sqlite3_prepare_v2(DB, find_sql.c_str(), -1, &stmt, 0);

    // Checking for errors in preparing the statement
    if (exit != SQLITE_OK) {
        std::cerr << "Error preparing SQL statement: " << sqlite3_errmsg(DB) << std::endl;
        sqlite3_close(DB);
        return nullptr;
    }


    // Executing the SQL statement
    exit = sqlite3_step(stmt);
    if (exit == SQLITE_ROW) {
        PlayerAccount account;

        // Retrieving data from the result set
        account.playerID = sqlite3_column_int(stmt, 0);
        const char* username = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        const char* password = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        strcpy_s(account.playerName, sizeof(account.playerName), username);
        strcpy_s(account.password, sizeof(account.password), password);
        account.gamesPlayed = sqlite3_column_int(stmt, 3);
        account.gamesWin = sqlite3_column_int(stmt, 4);
        account.totalScore = sqlite3_column_int(stmt, 5);

        std::cout << "Information:" << account.playerID << ", " << account.playerName << ", " << account.password << ", " << account.gamesPlayed << ", " << account.gamesWin << ", " << account.totalScore;
        // Closing the statement and database

        sqlite3_finalize(stmt);
        sqlite3_close(DB);

        // Returning the found account
        return &account;
    }
    std::cout << "check FAIL";
    // Finalizing the statement and closing the database
    sqlite3_finalize(stmt);
    sqlite3_close(DB);
    return nullptr;
}
void updatePlayer(const char* s, ::vector<PlayerAccount>& accounts, int playerID, int plusScore, bool win) {


    sqlite3* DB;
    //  char* messageError;

    int winC = 0;
    if (win) winC = 1;

    string sql = "UPDATE Players SET totalScore = totalScore + " + std::to_string(plusScore) + ", gamesplayed = gamesplayed + " + std::to_string(1) + ", gameswin = gameswin + " + std::to_string(winC) + " WHERE playerID = " + std::to_string(playerID);

    std::cout << "|||" << sql << "|||";
    int exit = sqlite3_open(s, &DB);
    if (exit != SQLITE_OK) {
        std::cout << "Fail open dtb!\n";
        return;
    }
    else {
        std::cout << "Succesfull open dtb!\n";
    }
    /* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
    //exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
    sqlite3_stmt* stmt;
    exit = sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, 0);
    exit = sqlite3_step(stmt);
    if (exit == SQLITE_ROW) {
        cerr << "Error in insertData function." << endl;
        //sqlite3_free(messageError);
        return;
    }
    else {
        cout << "Records inserted successfully!" << endl;
    }

    sqlite3_close(DB); // Close the connection after use

    return;

}
int addAccount(const char* s, const char* in_username, const char* in_password) {
    in_password = encodePass(in_password);
    sqlite3* DB;
    sqlite3_stmt* stmt;

    // Opening the database
    int exit = sqlite3_open(s, &DB);

    if (exit != SQLITE_OK) {
        std::cerr << "Error opening database: " << s << std::endl;
        return -1; // Returning accounts.end() since the database couldn't be opened
    }

    std::string check_sql = "SELECT * FROM Players WHERE username = " + std::string(in_username);

    // Preparing the SQL statement
    exit = sqlite3_prepare_v2(DB, check_sql.c_str(), -1, &stmt, 0);
    exit = sqlite3_step(stmt);
    if (exit == SQLITE_ROW) {
        std::cerr << "Exist username: " << sqlite3_errmsg(DB) << std::endl;
        sqlite3_close(DB);
        return -1;
    }

    std::string cnt_sql = "select count(distinct playerID) from Players ";
    exit = sqlite3_prepare_v2(DB, cnt_sql.c_str(), -1, &stmt, 0);
    exit = sqlite3_step(stmt);
    int cnt;
    if (exit == SQLITE_ROW) {
        cnt = sqlite3_column_int(stmt, 0);
        
    }

    std::string add_sql = "INSERT INTO Players(playerID, username, password, gamesplayed, gameswin, totalscore) VALUES(" + std::to_string(cnt + 1) + ",'" + std::string(in_username) + "', '" + std::string(in_password) + "'," + std::to_string(0) + "," + std::to_string(0) + "," + std::to_string(0) + ")";
    std::cout << add_sql << "\n";
    char* messageError;
    exit = sqlite3_exec(DB, add_sql.c_str(), NULL, 0, &messageError);

    if (exit != SQLITE_OK) {
        cerr << "Error in insertData function." << endl;
        sqlite3_free(messageError);
    }
    else {
        cout << "Records inserted successfully!" << endl;
    }
    std::cout << "Insert successfully!\n";
    return allAccounts.size();

}
static int createTable(const char* s)
{


    sqlite3* DB;
    char* messageError;
    cout << "Hello from create table!\n";

    string sql = R"(CREATE TABLE Player (
        ID	INTEGER,
        Username	TEXT UNIQUE,
        Password	TEXT,
        Point	INTEGER DEFAULT 0,
        EmailOrPhone	TEXT UNIQUE,
        PRIMARY KEY(ID AUTOINCREMENT)
        ); )";

    int exit = sqlite3_open(s, &DB);
    /* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);

    if (exit != SQLITE_OK) {
        cerr << "Error in createTable function." << endl;
        cerr << messageError << endl;
        sqlite3_free(messageError);
    }
    else {
        cout << "Table created successfully!" << endl;
    }

    sqlite3_close(DB); // Close the connection after use

    return 0;
}

void writePlayerAccountsToFile(const char* s, const std::vector<PlayerAccount>& accounts)
{
    sqlite3* DB;
    char* messageError;

    int exit = sqlite3_open(s, &DB);
    if (exit != SQLITE_OK) {
        std::cerr << "Error opening database: " << s << std::endl;
        return;
    }
    for (int i = 0; i < allAccounts.size(); i++)
    {
        cout << allAccounts[i].playerID << ", " << allAccounts[i].playerName << "\n";
    }

    std::string delete_sql = "DELETE FROM Players";
    int delete_res = sqlite3_exec(DB, delete_sql.c_str(), NULL, 0, &messageError);
    if (delete_res != SQLITE_OK) {
        std::cout << "Delete fail!\n";
    }
    else std::cout << "Delete successfully!\n";
    // Write each PlayerAccount to the DATABASE
    for (const auto& account : accounts)
    {
        std::string sql = "INSERT INTO Players(playerID, username, password, gamesplayed, gameswin, totalscore) VALUES(" + std::to_string(account.playerID) + ",'" + std::string(account.playerName) + "', '" + std::string(account.password) + "'," + std::to_string(account.gamesPlayed) + "," + std::to_string(account.gamesWin) + "," + std::to_string(account.totalScore) + ")";
        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
        if (exit != SQLITE_OK) {
            std::cerr << "Error when insert playerID: " << account.playerID << std::endl;
            return;

        }

    }

    sqlite3_close(DB);


    // Close the file

}
