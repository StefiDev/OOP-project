#include "task_types.h"
#include <sstream>

using namespace std;

// --- BasicTask ---

BasicTask::BasicTask(const string& title, const string& description, Priority priority, const string& deadline)
    : Task(title, description, priority, deadline) {}

BasicTask::BasicTask(const BasicTask& other) : Task(other) {}

string BasicTask::getType() const { return "Basic"; }

// clone() използва copy constructor — създава точно копие на обекта.
// Връща Task* (базов тип), но реално връща BasicTask обект — полиморфизъм.
Task* BasicTask::clone() const { return new BasicTask(*this); }

// --- BugTask ---

BugTask::BugTask(const string& title, const string& description, Priority priority, const string& deadline, const string& steps)
    : Task(title, description, priority, deadline), stepsToReproduce(steps) {}

BugTask::BugTask(const BugTask& other) : Task(other), stepsToReproduce(other.stepsToReproduce) {}

string BugTask::getType() const { return "Bug"; }

string BugTask::getStepsToReproduce() const { return stepsToReproduce; }

void BugTask::setStepsToReproduce(const string& steps) { stepsToReproduce = steps; }

string BugTask::toString() const {
    ostringstream oss;
    // Викаме базовата версия Task::toString() и добавяме само специфичното за BugTask.
    // Това е добро използване на наследяването — не копираме код.
    oss << Task::toString();
    oss << "Steps to reproduce: " << stepsToReproduce << "\n";
    return oss.str();
}

Task* BugTask::clone() const { return new BugTask(*this); }

// --- FeatureTask ---

FeatureTask::FeatureTask(const string& title, const string& description, Priority priority, const string& deadline, int hours)
    : Task(title, description, priority, deadline), estimatedHours(hours) {}

FeatureTask::FeatureTask(const FeatureTask& other) : Task(other), estimatedHours(other.estimatedHours) {}

string FeatureTask::getType() const { return "Feature"; }

int FeatureTask::getEstimatedHours() const { return estimatedHours; }

void FeatureTask::setEstimatedHours(int hours) { estimatedHours = hours; }

string FeatureTask::toString() const {
    ostringstream oss;
    oss << Task::toString();
    oss << "Estimated hours: " << estimatedHours << "\n";
    return oss.str();
}

Task* FeatureTask::clone() const { return new FeatureTask(*this); }
