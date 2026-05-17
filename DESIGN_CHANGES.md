# Design Changes from Checkpoint 1

The following changes were made to the original design described in `Мениджър_на_задачи_v5.docx`:

## 1. Task Inheritance Hierarchy (major change)

**Original:** A single concrete `Task` class with all fields.

**Implemented:** An abstract `Task` base class with three concrete subclasses:
- `BasicTask` — standard task
- `BugTask` — adds `stepsToReproduce` field
- `FeatureTask` — adds `estimatedHours` field

**Why:** Allows different task types with type-specific fields and behavior (overridden `toString()`). Uses polymorphism and virtual functions covered in lessons 7–8. The `clone()` pure virtual method enables correct deep copying of tasks without knowing the concrete type.

## 2. Plain enum instead of enum class

**Original:** `enum class Priority` and `enum class Status`.

**Implemented:** Plain `enum Priority` and `enum Status`.

**Why:** `enum class` requires explicit casting (e.g., `static_cast<int>`) when used in comparisons or saved to file. Plain enums are simpler and sufficient for this project's scope.

## 3. getStats() returns string instead of showStats() printing

**Original:** `showStats() : void` (prints directly to cout).

**Implemented:** `getStats() : string` (returns formatted string).

**Why:** Returning a string is more reusable — the menu can print it with `cout`, and it can also be used in tests without needing to capture stdout.

## 4. Rule of Three added to Project

**Original:** Only a destructor was specified.

**Implemented:** Copy constructor and copy assignment operator added alongside the destructor.

**Why:** The class manages heap memory (`vector<Task*>`). Without a copy constructor, copying a `Project` would result in a shallow copy and a double-free. The Rule of Three requires all three to be defined together.

## 5. Private taskMenu() helper in ProjectManager

**Original:** Single `showMenu()` method handles the entire terminal interface.

**Implemented:** `showMenu()` handles the top-level project menu; `taskMenu(Project*)` is a private helper that handles the task-level menu.

**Why:** Separating the two menus keeps each method readable and follows Single Responsibility within the class.
