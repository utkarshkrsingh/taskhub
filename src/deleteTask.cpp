#include <iostream>
#include <string>

#include "../include/deleteTask.h"
using namespace std;

void deleteTask(sqlite3 *db, sqlite3_stmt *stmt) {

    string title;
    cout << "Enter the title of task to delete : ";
    getline(cin, title);

    string query = "DELETE FROM todolist WHERE title=?;";
    int result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
    if (result != SQLITE_OK) {
        cerr << "failed to prepare statement : " << sqlite3_errmsg(db) << " (error code : " << result << ")" << endl;
        return;
    }

    result = sqlite3_bind_text(stmt, 1, title.c_str(), title.length(), SQLITE_TRANSIENT);
    if (result != SQLITE_OK) {
        cerr << "failed to bind task title : " << sqlite3_errmsg(db) << " (error code : " << result << ")" << endl;
        return;
    }

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return;
}
