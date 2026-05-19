#pragma once

#include <string>
#include <vector>
#include "project.h"
#include "task_types.h"

using namespace std;

// ProjectManager е "входната точка" на приложението — управлява проекти и
// осигурява менюто за потребителя. Той зависи от Project и Task, но не е
// нужно да знае детайлите на конкретните типове задачи (освен при създаване).

class ProjectManager {
private:
    // ЕНКАПСУЛАЦИЯ: projects и filePath са private — само методите на класа
    // решават кога се записва файл и как се управляват проектите.
    vector<Project*> projects;
    string filePath;
    // taskMenu е private — вътрешен детайл на имплементацията, не е публичен интерфейс.
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
