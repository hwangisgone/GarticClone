#include <sqlite3.h>
#include <iostream>

using namespace std;

bool found = false; // Flag to check if data is found

static int selectData(const char* s, const char* UserName, const char* Password);
static int callback(void* NotUsed, int argc, char** argv, char** azColName);
static int insertData(const char* s, const char* username, const char* password, const char* fullname, const char* emaiorphone);
static int createTable(const char* s);
int main() {
    const char* dir = "./data.db";

    char UserName[50];
    char Password[50];
    char FullName[50];
    char EmailOrPhone[50];

    int choose;
    createTable(dir);
    
        
        cout << "Sign up (1) OR Sign in (2): ";
    cin >> choose;

    if (choose == 1) {
        cout << "Name: ";
        cin >> UserName;

        cout << "Password: ";
        cin >> Password;

        cout << "FullName: ";
        cin >> FullName;

        cout << "Email Or Phone: ";
        cin >> EmailOrPhone;

        insertData(dir, UserName, Password, FullName, EmailOrPhone);
    }
    else if (choose == 2) {
        cout << "Name: ";
        cin >> UserName;

        cout << "Password: ";
        cin >> Password;

        selectData(dir, UserName, Password);
    }
    else {
        cout << "Invalid choice." << endl;
    }

    return 0;
}

static int selectData(const char* s, const char* UserName, const char* Password) {
    sqlite3* DB;
    char* messageError;

    string sql_username = "SELECT * FROM Player WHERE Username = '" + string(UserName) + "'";
    string sql = "SELECT * FROM Player WHERE Username = '" + string(UserName) + "' AND Password = '" + string(Password) + "'";

    int exit = sqlite3_open(s, &DB);

    if (exit != SQLITE_OK) {
        cerr << "Error opening the database." << endl;
        return 1;
    }

    exit = sqlite3_exec(DB, sql_username.c_str(), callback, NULL, &messageError);

    if (exit != SQLITE_OK) {
        cerr << "Error in selectData function." << endl;
        sqlite3_free(messageError);
    }
    else {
        if (found == true) {
            found = false;
            exit = sqlite3_exec(DB, sql.c_str(), callback, NULL, &messageError);
            if (exit != SQLITE_OK) {
                cerr << "Error in selectData function." << endl;
                sqlite3_free(messageError);
            }
            else {
                if (found == true) {
                    printf("Login successfully!\n");
                }
                else {
                    printf("Incorrect password!\n");
                }
            }
        }
        else {
            cout << "User not found!" << endl;
        }
    }

    sqlite3_close(DB); // Close the connection after use

    return 0;
}

static int insertData(const char* s, const char* username, const char* password, const char* fullname, const char* emaiorphone)
{
    sqlite3* DB;
    char* messageError;

    string sql = "INSERT INTO Player(Username, Password, Fullname, EmailOrPhone) VALUES('" + string(username) + "', '" + string(password) + "', '" + string(fullname) + "', '" + emaiorphone + "')";

    int exit = sqlite3_open(s, &DB);
    /* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);

    if (exit != SQLITE_OK) {
        cerr << "Error in insertData function." << endl;
        cerr << messageError << endl;
        sqlite3_free(messageError);
    }
    else {
        cout << "Records inserted successfully!" << endl;
    }

    sqlite3_close(DB); // Close the connection after use

    return 0;
}

static int createTable(const char* s)
{
    sqlite3* DB;
    char* messageError;
    cout << "Hello from create table!\n";
   
    string sql = R"(CREATE TABLE Player2 (
        ID	INTEGER,
        Username	TEXT UNIQUE,
        Password	TEXT,
        Point	INTEGER DEFAULT 0,
        Fullname    	TEXT,
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

static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
    found = true; // Set the flag when data is found

    for (int i = 0; i < argc; i++) {
        // column name and value
       // cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") << endl;
    }

    cout << endl;

    return 0;
}



