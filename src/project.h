#pragma once

#include <string>
#include <vector>
#include <ostream>
#include "task.h"

using namespace std;

// Project управлява колекция от задачи. Той не знае дали задачата е BasicTask,
// BugTask или FeatureTask — работи с тях само чрез базовия тип Task*.
// Това е класическо приложение на полиморфизъм и абстракция.

class Project {
private:
    // ЕНКАПСУЛАЦИЯ: name, description и tasks са private — никой отвън не може
    // директно да добавя задачи или да менте списъка. Единствено методите на класа
    // (addTask, removeTask) контролират достъпа.
    string name;
    string description;
    // ПОЛИМОРФИЗЪМ: пазим Task* указатели, не конкретни типове.
    // Така Project работи с всеки тип задача сега и в бъдеще.
    vector<Task*> tasks;
public:
    Project(const string& name, const string& description);
    // Copy constructor и operator= са нужни защото пазим raw указатели.
    // Без тях би се копирал само указателят — два обекта биха сочели към същата памет.
    Project(const Project& other);
    Project& operator=(const Project& other);
    // Деструкторът трие всяка задача от heap паметта — предотвратява memory leak.
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
