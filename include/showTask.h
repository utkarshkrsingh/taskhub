#ifndef SHOW_TASK_H
#define SHOW_TASK_H

#include <sqlite3.h>
#include <sys/ioctl.h>
#include <unistd.h>

void showAllTasks(sqlite3 *, sqlite3_stmt *);
void seperatingLine();

#endif
