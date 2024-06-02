#include <iostream>
#include <string>

#include "../include/insertTask.h"
using namespace std;

void insertData(sqlite3 *db, sqlite3_stmt *stmt) {

    string query = "INSERT INTO todolist (title, desc, date, time, status) VALUES(?,?,?,?,?);";
    string title;
    string desc;
    string dateOfCompletion;
    string timeOfCompletion;
    string status = "undone";

    cout << "Enter title (1-50) : ";
    getline(cin, title);

    cout << "Enter description (1-150) : ";
    getline(cin, desc);

    cout << "Enter completion date (YYYY:MM:DD) : ";
    getline(cin, dateOfCompletion);

    cout << "Enter completion time (HH:MM:SS) : ";
    getline(cin, timeOfCompletion);
    
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

    result = sqlite3_bind_text(stmt, 2, desc.c_str(), desc.length(), SQLITE_TRANSIENT);
    if (result != SQLITE_OK) {
        cerr << "failed to bind task description : " << sqlite3_errmsg(db) << " (error code : " << result << ")" << endl;
        return;
    }
    
    result = sqlite3_bind_text(stmt, 3, dateOfCompletion.c_str(), dateOfCompletion.length(), SQLITE_TRANSIENT);
    if (result != SQLITE_OK) {
        cerr << "failed to bind task completion date : " << sqlite3_errmsg(db) << " (error code : " << result << ")" << endl;
        return;
    }
    
    result = sqlite3_bind_text(stmt, 4, timeOfCompletion.c_str(), timeOfCompletion.length(), SQLITE_TRANSIENT);
    if (result != SQLITE_OK) {
        cerr << "failed to bind task completion time : " << sqlite3_errmsg(db) << " (error code : " << result << ")" << endl;
        return;
    }

    result = sqlite3_bind_text(stmt, 5, status.c_str(), status.length(), SQLITE_TRANSIENT);
    if (result != SQLITE_OK) {
        cerr << "failed to bind task status : " << sqlite3_errmsg(db) << " (error code : " << result << ")" << endl;
        return;
    }

    result = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    cout << "data inserted" << endl;
    return;
}
