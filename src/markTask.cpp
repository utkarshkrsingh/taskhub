#include <iostream>
#include <string>

#include "../include/markTask.h"
using namespace std;

void markDone(sqlite3 *db, sqlite3_stmt *stmt) {

    string title;
    cout << "Enter the title of the task to mark it as 'done' : ";
    getline(cin, title);

    string statusDone = "done";
    string query = "UPDATE todolist SET status=? WHERE title=?;";
    int result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
    if (result != SQLITE_OK) {
        cerr << "failed to prepare statement : " << sqlite3_errmsg(db) << " (error code : " << result << ")" << endl;
        return;
    }

    result = sqlite3_bind_text(stmt, 1, statusDone.c_str(), statusDone.length(), SQLITE_STATIC);
    if (result != SQLITE_OK) {
        cerr << "failed to bind done status : " << sqlite3_errmsg(db) << " (error code : " << result << ")" << endl;
        return;
    }

    result = sqlite3_bind_text(stmt, 2, title.c_str(), title.length(), SQLITE_STATIC);
    if (result != SQLITE_OK) {
        cerr << "failed to bind title : " << sqlite3_errmsg(db) << " (error code : " << result << ")" << endl;
        return;
    }

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return;
}
