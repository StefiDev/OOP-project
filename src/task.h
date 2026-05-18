#pragma once

#include <string>
#include <stdexcept>
#include <ostream>
#include "enums.h"

using namespace std;

// АБСТРАКЦИЯ: Task е абстрактен базов клас — не може да се създаде директно обект от него,
// защото има чисто виртуални методи (getType, clone). Той дефинира "какво е задача" без
// да казва "от какъв точен вид е". Подкласовете (BasicTask, BugTask, FeatureTask) задължително
// трябва да имплементират тези методи.

class Task {
protected:
    // ЕНКАПСУЛАЦИЯ: полетата са protected, не private, за да могат подкласовете да ги четат
    // директно при нужда, но extern код не може да ги достъпи без getters/setters.
    string title;
    string description;
    Priority priority;
    Status status;
    string deadline;
    string note;

    // Конструкторите са protected — само подкласове могат да викат Task(...).
    // Това гарантира, че Task не може да се инстанцира сам по себе си.
    Task(const string& title, const string& description, Priority priority, const string& deadline);
    Task(const Task& other);

public:
    // virtual ~Task е задължително при полиморфизъм с указатели:
    // ако имаме Task* t = new BugTask(...) и викнем delete t,
    // без virtual деструктора ще се извика само Task::~Task и паметта на BugTask ще изтече.
    virtual ~Task() = default;

    // ПОЛИМОРФИЗЪМ: getType() и clone() са чисто виртуални (= 0) — всеки подклас
    // трябва да ги override-не. toString() има базова имплементация, но подкласовете
    // могат да я разширят (BugTask и FeatureTask го правят).
    virtual string getType() const = 0;
    // clone() реализира "виртуален конструктор" — нужен е защото не можем да копираме
    // полиморфен обект чрез обикновен copy constructor (Project трябва да копира Task* без
    // да знае точния тип).
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
