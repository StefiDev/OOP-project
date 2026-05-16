#pragma once
#include "task.h"

using namespace std;

class BasicTask : public Task {
public:
    BasicTask(const string& title, const string& description, Priority priority, const string& deadline);
    BasicTask(const BasicTask& other);
    string getType() const override;
    Task* clone() const override;
};

class BugTask : public Task {
private:
    string stepsToReproduce;
public:
    BugTask(const string& title, const string& description, Priority priority, const string& deadline, const string& steps = "");
    BugTask(const BugTask& other);
    string getType() const override;
    string getStepsToReproduce() const;
    void setStepsToReproduce(const string& steps);
    string toString() const override;
    Task* clone() const override;
};

class FeatureTask : public Task {
private:
    int estimatedHours;
public:
    FeatureTask(const string& title, const string& description, Priority priority, const string& deadline, int hours = 0);
    FeatureTask(const FeatureTask& other);
    string getType() const override;
    int getEstimatedHours() const;
    void setEstimatedHours(int hours);
    string toString() const override;
    Task* clone() const override;
};
