#include <asm-generic/ioctls.h>
#include <iostream>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>

#include "../include/showTask.h"
using namespace std;

void seperatingLine();

void showAllTasks(sqlite3 *db, sqlite3_stmt *stmt) {
    
    string query = "SELECT * FROM todolist;";
    int result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
    if (result != SQLITE_OK) {
        cerr << "failed to prepare statement : " << sqlite3_errmsg(db) << " (error code : " << result << ")" << endl;
        return;
    }
    seperatingLine();
    while ((result = sqlite3_step(stmt)) == SQLITE_ROW) {
        cout << "Title\t\t: " << sqlite3_column_text(stmt, 0) << endl;
        cout << "Description\t: " << sqlite3_column_text(stmt, 1) << endl;
        cout << "Date\t\t: " << sqlite3_column_text(stmt, 2) << endl;
        cout << "Time\t\t: " << sqlite3_column_text(stmt, 3) << endl;
        cout << "Status\t\t: " << sqlite3_column_text(stmt, 4) << endl;

        seperatingLine();
    }

    return;
}

void seperatingLine() {
    struct winsize wsize;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &wsize);
    int width = wsize.ws_col;

    for (int i = 0; i < width; ++i) {
        cout << '-';
    }
    cout << endl;
    return;
}
