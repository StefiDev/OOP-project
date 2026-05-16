#pragma once

#include <string>
#include <stdexcept>
#include <ostream>
#include "enums.h"

using namespace std;

class Task {
protected:
    string title;
    string description;
    Priority priority;
    Status status;
    string deadline;
    string note;

    Task(const string& title, const string& description, Priority priority, const string& deadline);
    Task(const Task& other);

public:
    virtual ~Task() = default;

    virtual string getType() const = 0;
    virtual Task* clone() const = 0;
    virtual string toString() const;

    string getTitle() const;
    void setTitle(string t);

    string getDescription() const;
    void setDescription(string d);

    Priority getPriority() const;
    void setPriority(Priority p);

    Status getStatus() const;
    void setStatus(Status s);

    string getDeadline() const;
    void setDeadline(string deadline);

    string getNote() const;
    void setNote(string n);

    bool isOverdue() const;

    bool operator<(const Task& other) const;
    friend ostream& operator<<(ostream& os, const Task& t);
};
