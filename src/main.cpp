#include <filesystem>
#include <iostream>
#include <string>
#include <sqlite3.h>
#include <cstdlib>
#include <unistd.h>
using namespace std;

#include "../include/insertTask.h"
#include "../include/showTask.h"
#include "../include/deleteTask.h"
#include "../include/markTask.h"
#include "../include/help.h"

string getPath();
void connection(sqlite3 **, sqlite3_stmt *stmt, string);

int main(int argc, char *argv[]) {

    // verify for one argument only, each time the application is called
    if (argc < 2) {
        cout << "too few arguments" << endl;
        exit(1);
    } else if (argc > 2) {
        cout << "too many arguments" << endl;
        exit(1);
    }

    string dirPath = getPath();
    string dbPath = dirPath + "todolist.db";

    sqlite3 *db;
    sqlite3_stmt *stmt = nullptr;

    connection(&db, stmt, dbPath);

    // getting the argument i.e passed by user
    string argument = argv[1];
    if (argument == "insert" || argument == "-i") {
        insertData(db, stmt);
    } else if (argument == "delete" || argument == "-d") {
        deleteTask(db, stmt);
    } else if (argument == "mark" || argument == "-m") {
        markDone(db, stmt);
    } else if (argument == "show" || argument == "-s") {
        showAllTasks(db, stmt);
    } else if (argument == "help" || argument == "-h") {
        helpMsg();
    } else {
        cerr << "error : unexpected argument '" << argument << "' found\n"
            << "For more information, try 'todolist -h'." << endl;
    }

    sqlite3_close(db);
    return 0;
}

string getPath() {
    const char* homeDir = getenv("HOME");
    if (homeDir == nullptr) {
        cout << "home environment variable not set" << endl;
        exit(1);
    }
    filesystem::create_directory(string(homeDir) + "/.todolist/");
    return (string(homeDir) + "/.todolist/");
}

void connection(sqlite3 **db, sqlite3_stmt *stmt, string dbPath) {

    if (sqlite3_open(dbPath.c_str(), db) == SQLITE_OK) {
        string query = "CREATE TABLE IF NOT EXISTS todolist(title varchar(50), desc varchar(150), date char(10), time char(8), status varchar(10));";
        int result = sqlite3_prepare(*db, query.c_str(), -1, &stmt, NULL);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
        if (result != SQLITE_OK) {
            cerr << "table creation error" << endl;
            exit(1);
        }
        return;
    }

    cerr << "database connection not stablished" << endl;
    exit(1);
    return;
}
