#include <iostream>
#include "../include/help.h"
using namespace std;

void helpMsg() {

    cout << "A cli-based todolist\n" 
        << "Usage: todolist [OPTION]\n"
        << "Options:\n"
        << "    -h      Display this message\n"
        << "    -s      List all tasks\n"
        << "    -i      Add a new task\n"
        << "    -d      Delete a task\n"
        << "    -m      Update tasks as done" << endl;

    return;
}
