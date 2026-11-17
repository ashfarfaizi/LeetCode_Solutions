// cli-todo: a tiny task list stored in a plain text file.
#pragma once

#include <iosfwd>
#include <optional>
#include <string>
#include <vector>

namespace todo {

enum class Priority { Low = 0, Normal = 1, High = 2 };

// "low"/"normal"/"high" (also "l"/"n"/"h"), case-sensitive.
std::optional<Priority> parsePriority(const std::string& s);
const char* priorityName(Priority p);

struct Task {
    int id = 0;
    std::string text;
    bool done = false;
    Priority priority = Priority::Normal;
};

struct Stats {
    int total = 0;
    int done = 0;
    int pending = 0;
    int pendingByPriority[3] = {0, 0, 0};  // indexed by Priority
};

class TodoList {
public:
    // Appends a task and returns its id. Ids are never reused.
    int add(const std::string& text, Priority p = Priority::Normal);

    // Marks a task done; returns false if no task has that id.
    bool complete(int id);

    // Marks a completed task as pending again; returns false if no task has
    // that id.
    bool reopen(int id);

    // Deletes a task; returns false if no task has that id.
    bool remove(int id);

    // Replaces a task's text; returns false if no task has that id.
    bool edit(int id, const std::string& text);

    // Changes a task's priority; returns false if no task has that id.
    bool setPriority(int id, Priority p);

    // Deletes every completed task and returns how many were removed.
    int clearDone();

    // Tasks ordered for display: higher priority first, then by id.
    std::vector<Task> sorted() const;

    // Tasks whose text contains `needle`, ignoring ASCII case, in display
    // order. An empty needle matches every task.
    std::vector<Task> search(const std::string& needle) const;

    Stats stats() const;

    std::optional<Task> find(int id) const;
    const std::vector<Task>& tasks() const { return tasks_; }
    int nextId() const { return nextId_; }

    // Text format: a "# cli-todo v2" header, then one
    // "id<TAB>done<TAB>priority<TAB>text" line per task, where done is 0 or 1
    // and priority is L, N or H. Files with a v1 header (no priority column)
    // still load, with every task at normal priority.
    void save(std::ostream& out) const;
    static TodoList load(std::istream& in);  // throws std::runtime_error

    // A missing file loads as an empty list.
    static TodoList loadFile(const std::string& path);
    void saveFile(const std::string& path) const;

private:
    Task* findMut(int id);

    std::vector<Task> tasks_;
    int nextId_ = 1;
};

// "[ ] 3  buy milk" / "[x] 4  call mum" / "[ ] 5  (high) pay rent"
std::string format(const Task& t);

}  // namespace todo
