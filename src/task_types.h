#pragma once
#include "task.h"

using namespace std;

// НАСЛЕДЯВАНЕ: BasicTask, BugTask и FeatureTask наследяват Task.
// Всеки наследник добавя специфични данни и override-ва виртуалните методи.
// Общото поведение (title, deadline, status...) е дефинирано веднъж в Task — не се повтаря.

// Най-простата задача — само override-ва getType() и clone(), без допълнителни полета.
class BasicTask : public Task {
public:
    BasicTask(const string& title, const string& description, Priority priority, const string& deadline);
    BasicTask(const BasicTask& other);
    string getType() const override;
    Task* clone() const override;
};

// BugTask разширява Task с поле stepsToReproduce, специфично за бъгове.
// ЕНКАПСУЛАЦИЯ: stepsToReproduce е private — достъпно само чрез getter/setter.
// toString() е override-нат, за да включи допълнителното поле в изхода.
class BugTask : public Task {
private:
    string stepsToReproduce;
public:
    BugTask(const string& title, const string& description, Priority priority, const string& deadline, const string& steps = "");
    BugTask(const BugTask& other);
    string getType() const override;
    string getStepsToReproduce() const;
    void setStepsToReproduce(const string& steps);
    string toString() const override;  // разширява Task::toString() с допълнителните данни
    Task* clone() const override;
};

// FeatureTask разширява Task с estimatedHours — специфично за нови функционалности.
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
