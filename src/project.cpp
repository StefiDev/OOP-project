#include "project.h"
#include <sstream>
#include <algorithm>

using namespace std;

Project::Project(const string& name, const string& description) : name(name), description(description) {}

Project::Project(const Project& other) : name(other.name), description(other.description) {
    // ПОЛИМОРФИЗЪМ: clone() се вика виртуално — всяка задача се копира като
    // правилния си подтип. Ако не ползвахме clone(), щяхме да загубим
    // специфичните данни (stepsToReproduce, estimatedHours) при копиране.
    for (size_t i = 0; i < other.tasks.size(); i++) {
        tasks.push_back(other.tasks[i]->clone());
    }
}

Project& Project::operator=(const Project& other) {
    // Self-assignment guard: ако p = p, не трием собствените си задачи.
    if (this == &other) return *this;
    for (size_t i = 0; i < tasks.size(); i++) delete tasks[i];
    tasks.clear();
    name = other.name;
    description = other.description;
    for (size_t i = 0; i < other.tasks.size(); i++) {
        tasks.push_back(other.tasks[i]->clone());
    }
    return *this;
}

Project::~Project() {
    for (size_t i = 0; i < this->tasks.size(); i++) delete this->tasks[i];
    this->tasks.clear();
}

string Project::getName() const { return this->name; }
void Project::setName(string n) { if (n.empty()) throw invalid_argument("Can't be empty"); this->name = n; }

string Project::getDescription() const { return this->description; }
void Project::setDescription(string d) { if (d.empty()) throw invalid_argument("Can't be empty"); this->description = d; }

vector<Task*> Project::getTasks() const { return this->tasks; }

void Project::addTask(Task* t) {
    if (t == nullptr) throw invalid_argument("Task can't be nullptr");
    this->tasks.push_back(t);
}

bool Project::removeTask(string title) {
    for (size_t i = 0; i < this->tasks.size(); i++) {
        if (this->tasks[i]->getTitle() == title) {
            delete this->tasks[i];
            this->tasks.erase(this->tasks.begin() + i);
            return true;
        }
    }
    return false;
}

vector<Task*> Project::getTasksByStatus(Status s) const {
    vector<Task*> filtered;
    for (size_t i = 0; i < this->tasks.size(); i++) {
        if (this->tasks[i]->getStatus() == s) filtered.push_back(this->tasks[i]);
    }
    return filtered;
}

vector<Task*> Project::getTasksByPriority(Priority p) const {
    vector<Task*> filtered;
    for (size_t i = 0; i < this->tasks.size(); i++) {
        if (this->tasks[i]->getPriority() == p) filtered.push_back(this->tasks[i]);
    }
    return filtered;
}

void Project::sortTasksByDeadline() {
    for (size_t i = 0; i < this->tasks.size(); i++) {
        for (size_t j = i + 1; j < this->tasks.size(); j++) {
            // *tasks[j] < *tasks[i] вика Task::operator< — дереференцираме указателите,
            // за да сравним обектите, не адресите им в паметта.
            if (*this->tasks[j] < *this->tasks[i]) swap(this->tasks[i], this->tasks[j]);
        }
    }
}

void Project::sortTasksByPriority() {
    for (size_t i = 0; i < this->tasks.size(); i++) {
        for (size_t j = i + 1; j < this->tasks.size(); j++) {
            if (this->tasks[i]->getPriority() < this->tasks[j]->getPriority()) swap(this->tasks[i], this->tasks[j]);
        }
    }
}

string Project::getStats() const {
    int total = this->tasks.size();
    int done = 0, inProgress = 0, overdue = 0;
    for (size_t i = 0; i < this->tasks.size(); i++) {
        Status s = this->tasks[i]->getStatus();
        if (s == Status::DONE) done++;
        else if (s == Status::IN_PROGRESS) inProgress++;
        if (this->tasks[i]->isOverdue()) overdue++;
    }
    ostringstream oss;
    oss << "Total tasks: " << total << "\n";
    oss << "Done: " << done << "\n";
    oss << "In progress: " << inProgress << "\n";
    oss << "Overdue: " << overdue << "\n";
    return oss.str();
}

string Project::toString() const {
    ostringstream oss;
    oss << "Project: " << name << " - " << description << "\n";
    oss << "Tasks: " << this->tasks.size() << "\n";
    for (size_t i = 0; i < this->tasks.size(); i++) {
        oss << "- " << *this->tasks[i] << "\n";
    }
    return oss.str();
}

ostream& operator<<(ostream& os, const Project& p) {
    os << p.toString();
    return os;
}
