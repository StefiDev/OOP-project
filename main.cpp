#include "src/project_manager.h"

// Входна точка на програмата. Цялата логика е скрита зад ProjectManager —
// main не знае нищо за Task, Project или файловете. Това е добра енкапсулация на ниво архитектура.

int main() {
    ProjectManager manager("data.txt");
    manager.showMenu();
    return 0;
}
