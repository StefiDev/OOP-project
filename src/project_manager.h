#pragma once

#include <string>
#include <vector>
#include "project.h"
#include "task_types.h"

using namespace std;

class ProjectManager {
private:
    vector<Project*> projects;
    string filePath;
    void taskMenu(Project* project);
public:
    ProjectManager(const string& filePath);
    ~ProjectManager();
    void addProject(const string& name, const string& desc);
    bool removeProject(const string& name);
    Project* getProject(const string& name) const;
    void listProjects() const;
    void saveToFile() const;
    void loadFromFile();
    void showMenu();
};
