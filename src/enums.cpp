#include "enums.h"
#include <sstream>

using namespace std;

string priorityToString(Priority p) {
    switch (p) {
        case Priority::LOW: return "Low";
        case Priority::MEDIUM: return "Medium";
        case Priority::HIGH: return "High";
    }
    return "";
}

string statusToString(Status s) {
    switch (s) {
        case Status::TODO: return "To Do";
        case Status::IN_PROGRESS: return "In Progress";
        case Status::DONE: return "Done";
    }
    return "";
}

vector<string> splitString(const string& str, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(str);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

Priority strToPriority(const string& str) {
    if (str == "Low") return Priority::LOW;
    else if (str == "Medium") return Priority::MEDIUM;
    return Priority::HIGH;
}

Status strToStatus(const string& str) {
    if (str == "To Do") return Status::TODO;
    else if (str == "In Progress") return Status::IN_PROGRESS;
    return Status::DONE;
}
