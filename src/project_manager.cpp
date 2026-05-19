#include "project_manager.h"
#include "enums.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

void ProjectManager::taskMenu(Project* project) {
    int choice;
    while (true) {
        cout << "\n--- Task Menu: " << project->getName() << " ---\n";
        cout << "1. Add Task\n";
        cout << "2. Remove Task\n";
        cout << "3. List Tasks\n";
        cout << "4. Mark Task as Done\n";
        cout << "5. Mark Task as In Progress\n";
        cout << "6. List Tasks by Priority\n";
        cout << "7. List Tasks by Status\n";
        cout << "8. List Overdue Tasks\n";
        cout << "9. Sort Tasks by Deadline\n";
        cout << "10. Sort Tasks by Priority\n";
        cout << "11. Statistics\n";
        cout << "12. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;
        if (cin.fail()) { cin.clear(); cin.ignore(1000, '\n'); cout << "Invalid input.\n"; continue; }

        if (choice == 1) {
            cout << "Task type (1=Basic, 2=Bug, 3=Feature): ";
            int type; cin >> type; cin.ignore(1000, '\n');
            if (type < 1 || type > 3) { cout << "Invalid type.\n"; continue; }

            string name, desc, deadline;
            cout << "Task name: "; getline(cin >> ws, name);
            cout << "Description: "; getline(cin >> ws, desc);
            cout << "Deadline (YYYY-MM-DD): "; getline(cin >> ws, deadline);
            cout << "Priority (0=Low, 1=Medium, 2=High): ";
            int pi; cin >> pi; cin.ignore(1000, '\n');
            if (pi < 0 || pi > 2) { cout << "Invalid priority.\n"; continue; }
            Priority p = (Priority)pi;

            Task* task;
            try {
                if (type == 2) {
                    string steps;
                    cout << "Steps to reproduce: "; getline(cin >> ws, steps);
                    task = new BugTask(name, desc, p, deadline, steps);
                } else if (type == 3) {
                    cout << "Estimated hours: ";
                    int hours; cin >> hours; cin.ignore(1000, '\n');
                    task = new FeatureTask(name, desc, p, deadline, hours);
                } else {
                    task = new BasicTask(name, desc, p, deadline);
                }
            } catch (const invalid_argument& e) {
                cout << "Error: " << e.what() << "\n"; continue;
            }
            project->addTask(task);
            saveToFile();
            cout << "Task added.\n";
        }
        else if (choice == 2) {
            string name; cout << "Task name: "; getline(cin >> ws, name);
            if (!project->removeTask(name)) cout << "Task not found.\n";
            else { cout << "Task removed.\n"; saveToFile(); }
        }
        else if (choice == 3) {
            vector<Task*> tasks = project->getTasks();
            if (tasks.empty()) cout << "No tasks.\n";
            else {
                for (size_t i = 0; i < tasks.size(); i++) cout << i + 1 << ". " << *tasks[i];
            }
        }
        else if (choice == 4) {
            string name; cout << "Task name: "; getline(cin >> ws, name);
            vector<Task*> tasks = project->getTasks(); bool found = false;
            for (size_t i = 0; i < tasks.size(); i++) {
                if (tasks[i]->getTitle() == name) {
                    tasks[i]->setStatus(Status::DONE);
                    cout << "Marked as Done.\n"; saveToFile(); found = true; break;
                }
            }
            if (!found) cout << "Task not found.\n";
        }
        else if (choice == 5) {
            string name; cout << "Task name: "; getline(cin >> ws, name);
            vector<Task*> tasks = project->getTasks(); bool found = false;
            for (size_t i = 0; i < tasks.size(); i++) {
                if (tasks[i]->getTitle() == name) {
                    tasks[i]->setStatus(Status::IN_PROGRESS);
                    cout << "Marked as In Progress.\n"; saveToFile(); found = true; break;
                }
            }
            if (!found) cout << "Task not found.\n";
        }
        else if (choice == 6) {
            cout << "Priority (0=Low, 1=Medium, 2=High): "; int pi; cin >> pi;
            if (pi < 0 || pi > 2) { cout << "Invalid priority.\n"; continue; }
            Priority p = (Priority)pi;
            vector<Task*> filtered = project->getTasksByPriority(p);
            if (filtered.empty()) cout << "No tasks.\n";
            for (size_t i = 0; i < filtered.size(); i++) cout << i + 1 << ". " << *filtered[i];
        }
        else if (choice == 7) {
            cout << "Status (0=To Do, 1=In Progress, 2=Done): "; int si; cin >> si;
            if (si < 0 || si > 2) { cout << "Invalid status.\n"; continue; }
            Status s = (Status)si;
            vector<Task*> filtered = project->getTasksByStatus(s);
            if (filtered.empty()) cout << "No tasks.\n";
            for (size_t i = 0; i < filtered.size(); i++) cout << i + 1 << ". " << *filtered[i];
        }
        else if (choice == 8) {
            vector<Task*> tasks = project->getTasks();
            bool any = false;
            for (size_t i = 0; i < tasks.size(); i++) {
                if (tasks[i]->isOverdue()) { cout << i + 1 << ". " << *tasks[i]; any = true; }
            }
            if (!any) cout << "No overdue tasks.\n";
        }
        else if (choice == 9) { project->sortTasksByDeadline(); saveToFile(); cout << "Sorted by deadline.\n"; }
        else if (choice == 10) { project->sortTasksByPriority(); saveToFile(); cout << "Sorted by priority.\n"; }
        else if (choice == 11) { cout << project->getStats(); }
        else if (choice == 12) { return; }
    }
}

ProjectManager::ProjectManager(const string& filePath) : filePath(filePath) { loadFromFile(); }

ProjectManager::~ProjectManager() {
    for (size_t i = 0; i < this->projects.size(); i++) delete this->projects[i];
    this->projects.clear();
}

void ProjectManager::addProject(const string& name, const string& desc) {
    for (size_t i = 0; i < this->projects.size(); i++) {
        if (this->projects[i]->getName() == name) { cout << "A project with that name already exists.\n"; return; }
    }
    this->projects.push_back(new Project(name, desc));
    cout << "Project \"" << name << "\" created.\n";
    saveToFile();
}

bool ProjectManager::removeProject(const string& name) {
    for (size_t i = 0; i < this->projects.size(); i++) {
        if (this->projects[i]->getName() == name) {
            delete this->projects[i];
            this->projects.erase(this->projects.begin() + i);
            cout << "Project deleted.\n"; saveToFile(); return true;
        }
    }
    cout << "Project not found.\n"; return false;
}

Project* ProjectManager::getProject(const string& name) const {
    for (size_t i = 0; i < this->projects.size(); i++) {
        if (this->projects[i]->getName() == name) return this->projects[i];
    }
    return nullptr;
}

void ProjectManager::listProjects() const {
    if (this->projects.empty()) { cout << "No projects.\n"; return; }
    cout << "\n=== Projects ===\n";
    for (size_t i = 0; i < this->projects.size(); i++) cout << i + 1 << ". " << *this->projects[i];
}

void ProjectManager::saveToFile() const {
    ofstream file(filePath);
    if (!file.is_open()) { cout << "Error saving file.\n"; return; }
    for (size_t i = 0; i < this->projects.size(); i++) {
        file << "PROJECT|" << this->projects[i]->getName() << "|" << this->projects[i]->getDescription() << "\n";
        vector<Task*> tasks = this->projects[i]->getTasks();
        for (size_t j = 0; j < tasks.size(); j++) {
            Task* t = tasks[j];
            file << "TASK|" << t->getType() << "|" << t->getTitle() << "|" << t->getDescription() << "|"
                 << priorityToString(t->getPriority()) << "|" << statusToString(t->getStatus()) << "|"
                 << t->getDeadline() << "|" << t->getNote();
            // dynamic_cast проверява типа на обекта по време на изпълнение.
            // Нужен е тук, защото saveToFile трябва да запише специфичните данни
            // (stepsToReproduce, estimatedHours) — те не съществуват в базовия Task.
            // Ако не бяхме ползвали полиморфизъм, щяхме да имаме отделни вектори
            // за всеки тип задача — много по-сложно.
            if (BugTask* bt = dynamic_cast<BugTask*>(t)) {
                file << "|" << bt->getStepsToReproduce();
            } else if (FeatureTask* ft = dynamic_cast<FeatureTask*>(t)) {
                file << "|" << ft->getEstimatedHours();
            }
            file << "\n";
        }
    }
    file.close();
}

void ProjectManager::loadFromFile() {
    ifstream file(filePath);
    if (!file.is_open()) return;
    for (size_t i = 0; i < this->projects.size(); i++) delete this->projects[i];
    this->projects.clear();
    Project* current = nullptr;
    string line;
    while (getline(file, line)) {
        vector<string> parts = splitString(line, '|');
        if (parts.empty()) continue;
        if (parts[0] == "PROJECT" && parts.size() >= 3) {
            current = new Project(parts[1], parts[2]);
            this->projects.push_back(current);
        }
        else if (parts[0] == "TASK" && current != nullptr) {
            // Detect format: new format has type in parts[1] ("Basic"/"Bug"/"Feature")
            string type = (parts.size() > 1) ? parts[1] : "";
            bool isNewFormat = (type == "Basic" || type == "Bug" || type == "Feature");

            if (isNewFormat && parts.size() >= 7) {
                string title = parts[2], desc = parts[3];
                Priority pri = strToPriority(parts[4]);
                Status stat = strToStatus(parts[5]);
                string deadline = parts[6];
                string note = (parts.size() > 7) ? parts[7] : "";
                Task* t;
                try {
                    if (type == "Bug") {
                        string steps = (parts.size() > 8) ? parts[8] : "";
                        t = new BugTask(title, desc, pri, deadline, steps);
                    } else if (type == "Feature") {
                        int hours = (parts.size() > 8 && !parts[8].empty()) ? stoi(parts[8]) : 0;
                        t = new FeatureTask(title, desc, pri, deadline, hours);
                    } else {
                        t = new BasicTask(title, desc, pri, deadline);
                    }
                    t->setStatus(stat);
                    if (!note.empty()) t->setNote(note);
                    current->addTask(t);
                } catch (...) {}
            } else if (!isNewFormat && parts.size() >= 6) {
                // Old format: TASK|title|desc|priority|status|deadline|note
                try {
                    Task* t = new BasicTask(parts[1], parts[2], strToPriority(parts[3]), parts[5]);
                    t->setStatus(strToStatus(parts[4]));
                    if (parts.size() > 6 && !parts[6].empty()) t->setNote(parts[6]);
                    current->addTask(t);
                } catch (...) {}
            }
        }
    }
    file.close();
}

void ProjectManager::showMenu() {
    while (true) {
        cout << "\n=============================\n";
        cout << "  TASK MANAGER\n";
        cout << "=============================\n";
        cout << "1. Show all projects\n";
        cout << "2. Create project\n";
        cout << "3. Open project\n";
        cout << "4. Delete project\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        int choice; cin >> choice;
        if (cin.fail()) { cin.clear(); cin.ignore(1000, '\n'); cout << "Invalid input.\n"; continue; }
        if (choice == 0) { cout << "Goodbye!\n"; break; }
        else if (choice == 1) listProjects();
        else if (choice == 2) {
            string name, desc;
            cout << "Project name: "; getline(cin >> ws, name);
            cout << "Description: "; getline(cin >> ws, desc);
            addProject(name, desc);
        }
        else if (choice == 3) {
            string name; cout << "Project name: "; getline(cin >> ws, name);
            Project* p = getProject(name);
            if (p == nullptr) cout << "Project not found.\n"; else taskMenu(p);
        }
        else if (choice == 4) {
            string name; cout << "Project name: "; getline(cin >> ws, name);
            removeProject(name);
        }
    }
}
