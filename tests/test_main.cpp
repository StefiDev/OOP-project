// Unit tests for OOP project classes
#define UNIT_TEST
#include "../src/enums.h"
#include "../src/task.h"
#include "../src/task_types.h"
#include "../src/project.h"
#include "../src/project_manager.h"
#include <cassert>
#include <iostream>
#include <cstdio>

using namespace std;

void testPriorityAndStatusConversions() {
    assert(priorityToString(Priority::LOW) == "Low");
    assert(priorityToString(Priority::MEDIUM) == "Medium");
    assert(priorityToString(Priority::HIGH) == "High");

    assert(statusToString(Status::TODO) == "To Do");
    assert(statusToString(Status::IN_PROGRESS) == "In Progress");
    assert(statusToString(Status::DONE) == "Done");

    assert(strToPriority("Low") == Priority::LOW);
    assert(strToPriority("Medium") == Priority::MEDIUM);
    assert(strToPriority("High") == Priority::HIGH);

    assert(strToStatus("To Do") == Status::TODO);
    assert(strToStatus("In Progress") == Status::IN_PROGRESS);
    assert(strToStatus("Done") == Status::DONE);
}

void testSplitString() {
    vector<string> v = splitString("a|b|c", '|');
    assert(v.size() == 3);
    assert(v[0] == "a" && v[1] == "b" && v[2] == "c");
}

void testTaskSettersGettersAndExceptions() {
    BasicTask t("T1", "Desc", Priority::MEDIUM, "2026-12-31");
    assert(t.getTitle() == "T1");
    assert(t.getDescription() == "Desc");
    assert(t.getPriority() == Priority::MEDIUM);
    assert(t.getStatus() == Status::TODO);
    assert(t.getDeadline() == "2026-12-31");

    bool threw = false;
    try { t.setTitle(""); } catch (invalid_argument&) { threw = true; }
    assert(threw);

    threw = false;
    try { t.setDescription(""); } catch (invalid_argument&) { threw = true; }
    assert(threw);

    threw = false;
    try { t.setDeadline(""); } catch (invalid_argument&) { threw = true; }
    assert(threw);

    threw = false;
    try { t.setNote(""); } catch (invalid_argument&) { threw = true; }
    assert(threw);

    t.setNote("Note");
    assert(t.getNote() == "Note");

    t.setStatus(Status::DONE);
    assert(t.getStatus() == Status::DONE);
}

void testTaskTypes() {
    BasicTask bt("t", "d", Priority::LOW, "2026-01-01");
    assert(bt.getType() == "Basic");

    BugTask bug("b", "d", Priority::HIGH, "2026-01-01", "click button");
    assert(bug.getType() == "Bug");
    assert(bug.getStepsToReproduce() == "click button");

    FeatureTask feat("f", "d", Priority::MEDIUM, "2026-01-01", 10);
    assert(feat.getType() == "Feature");
    assert(feat.getEstimatedHours() == 10);
}

void testTaskOperatorLessAndClone() {
    BasicTask earlier("e", "d", Priority::LOW, "2025-01-01");
    BasicTask later("l", "d", Priority::LOW, "2026-01-01");
    assert(earlier < later);
    assert(!(later < earlier));

    Task* cloned = earlier.clone();
    assert(cloned->getTitle() == "e");
    assert(cloned->getType() == "Basic");
    delete cloned;
}

void testIsOverdueBehavior() {
    BasicTask oldTask("old", "d", Priority::LOW, "2020-01-01");
    assert(oldTask.isOverdue());
    oldTask.setStatus(Status::DONE);
    assert(!oldTask.isOverdue());
}

void testProjectOperations() {
    Project p("Proj", "D");
    assert(p.getName() == "Proj");
    assert(p.getDescription() == "D");

    Task* t1 = new BasicTask("A", "a", Priority::HIGH, "2026-12-31");
    Task* t2 = new BasicTask("B", "b", Priority::LOW, "2025-01-01");
    p.addTask(t1);
    p.addTask(t2);

    vector<Task*> high = p.getTasksByPriority(Priority::HIGH);
    assert(high.size() == 1 && high[0]->getTitle() == "A");

    p.sortTasksByDeadline();
    vector<Task*> tasks = p.getTasks();
    assert(tasks.size() == 2);
    assert(tasks[0]->getTitle() == "B");

    assert(p.removeTask("A") == true);
    assert(p.removeTask("Nope") == false);
}

void testProjectCopyConstructor() {
    Project original("Orig", "desc");
    original.addTask(new BugTask("b1", "d", Priority::HIGH, "2026-01-01", "steps"));

    Project copy(original);
    assert(copy.getName() == "Orig");
    assert(copy.getTasks().size() == 1);
    assert(copy.getTasks()[0]->getType() == "Bug");
}

void testProjectManagerSaveLoad() {
    const char* fname = "test_data.txt";
    remove(fname);

    {
        ProjectManager m(fname);
        m.addProject("P1", "d1");
        Project* p = m.getProject("P1");
        assert(p != nullptr);
        p->addTask(new BugTask("b", "d", Priority::LOW, "2026-06-01", "repro"));
        p->addTask(new FeatureTask("f", "d", Priority::MEDIUM, "2026-07-01", 3));
        m.saveToFile();
    }

    {
        ProjectManager m2(fname);
        Project* p2 = m2.getProject("P1");
        assert(p2 != nullptr);
        vector<Task*> ts = p2->getTasks();
        assert(ts.size() == 2);
        assert(ts[0]->getType() == "Bug");
        assert(ts[1]->getType() == "Feature");
    }

    remove(fname);
}

int main() {
    try {
        testPriorityAndStatusConversions();
        testSplitString();
        testTaskSettersGettersAndExceptions();
        testTaskTypes();
        testTaskOperatorLessAndClone();
        testIsOverdueBehavior();
        testProjectOperations();
        testProjectCopyConstructor();
        testProjectManagerSaveLoad();
    } catch (const exception& e) {
        cerr << "Test failed with exception: " << e.what() << endl;
        return 1;
    }

    cout << "All tests passed." << endl;
    return 0;
}
