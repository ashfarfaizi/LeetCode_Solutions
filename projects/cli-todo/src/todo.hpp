// cli-todo: a tiny task list stored in a plain text file.
#pragma once

#include <iosfwd>
#include <optional>
#include <string>
#include <vector>

namespace todo {

struct Task {
    int id = 0;
    std::string text;
    bool done = false;
};

class TodoList {
public:
    // Appends a task and returns its id. Ids are never reused.
    int add(const std::string& text);

    // Marks a task done; returns false if no task has that id.
    bool complete(int id);

    std::optional<Task> find(int id) const;
    const std::vector<Task>& tasks() const { return tasks_; }
    int nextId() const { return nextId_; }

    // Text format: a "# cli-todo v1" header, then one "id<TAB>done<TAB>text"
    // line per task, where done is 0 or 1.
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

// "[ ] 3  buy milk" / "[x] 4  call mum"
std::string format(const Task& t);

}  // namespace todo
