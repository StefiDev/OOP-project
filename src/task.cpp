#include "task.h"
#include <sstream>
#include <ctime>

using namespace std;

Task::Task(const string& title, const string& description, Priority priority, const string& deadline) {
    this->title = title;
    this->description = description;
    this->priority = priority;
    setDeadline(deadline);
    this->status = Status::TODO;
    this->note = "";
}

Task::Task(const Task& other)
    : title(other.title), description(other.description), priority(other.priority),
      status(other.status), deadline(other.deadline), note(other.note) {}

string Task::getTitle() const { return this->title; }
void Task::setTitle(string t) {
    if (t.empty()) throw invalid_argument("Can't be empty");
    this->title = t;
}

string Task::getDescription() const { return this->description; }
void Task::setDescription(string d) {
    if (d.empty()) throw invalid_argument("Can't be empty");
    this->description = d;
}

Priority Task::getPriority() const { return this->priority; }
void Task::setPriority(Priority p) { this->priority = p; }

Status Task::getStatus() const { return this->status; }
void Task::setStatus(Status s) { this->status = s; }

string Task::getDeadline() const { return this->deadline; }
void Task::setDeadline(string deadline) {
    if (deadline.empty()) throw invalid_argument("Can't be empty");
    if (deadline.size() != 10 || deadline[4] != '-' || deadline[7] != '-') {
        throw invalid_argument("Deadline format must be: YYYY-MM-DD");
    }
    this->deadline = deadline;
}

string Task::getNote() const { return this->note; }
void Task::setNote(string n) {
    if (n.empty()) throw invalid_argument("Can't be empty");
    this->note = n;
}

bool Task::isOverdue() const {
    if (this->status == Status::DONE) return false;
    if (this->deadline.empty()) throw runtime_error("Deadline not set");
    time_t now = time(0);
    tm* localTime = localtime(&now);
    string today = to_string(1900 + localTime->tm_year) + "-";
    if ((1 + localTime->tm_mon) < 10) today += "0";
    today += to_string(1 + localTime->tm_mon) + "-";
    if (localTime->tm_mday < 10) today += "0";
    today += to_string(localTime->tm_mday);
    return this->deadline < today;
}

string Task::toString() const {
    ostringstream oss;
    oss << "[" << getType() << "] " << this->title << "\n";
    oss << "Desc: " << this->description << "\n";
    oss << "Priority: " << priorityToString(this->priority) << "\n";
    oss << "Status: " << statusToString(this->status) << "\n";
    oss << "Deadline: " << this->deadline << "\n";
    if (this->isOverdue()) oss << "[OVERDUE]\n";
    if (!this->note.empty()) oss << "Note: " << this->note << "\n";
    return oss.str();
}

bool Task::operator<(const Task& other) const {
    return this->deadline < other.deadline;
}

ostream& operator<<(ostream& os, const Task& t) {
    os << t.toString();
    return os;
}
