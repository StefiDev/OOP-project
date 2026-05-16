#pragma once

#include <string>
#include <vector>
#include <ostream>
#include "task.h"

using namespace std;

class Project {
private:
    string name;
    string description;
    vector<Task*> tasks;
public:
    Project(const string& name, const string& description);
    Project(const Project& other);
    Project& operator=(const Project& other);
    ~Project();

    string getName() const;
    void setName(string n);
    string getDescription() const;
    void setDescription(string d);
    vector<Task*> getTasks() const;
    void addTask(Task* t);
    bool removeTask(string title);
    vector<Task*> getTasksByStatus(Status s) const;
    vector<Task*> getTasksByPriority(Priority p) const;
    void sortTasksByDeadline();
    void sortTasksByPriority();
    string getStats() const;
    string toString() const;

    friend ostream& operator<<(ostream& os, const Project& p);
};
