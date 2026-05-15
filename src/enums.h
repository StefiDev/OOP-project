#pragma once
#include <string>
#include <vector>

using namespace std;

enum Priority {
    LOW,
    MEDIUM,
    HIGH
};

enum Status {
    TODO,
    IN_PROGRESS,
    DONE
};

string priorityToString(Priority p);
string statusToString(Status s);

vector<string> splitString(const string& str, char delimiter);

Priority strToPriority(const string& str);
Status strToStatus(const string& str);
