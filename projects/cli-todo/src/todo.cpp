#include "todo.hpp"

#include <algorithm>
#include <fstream>
#include <istream>
#include <ostream>
#include <stdexcept>

namespace todo {

namespace {

const char* const kHeader = "# cli-todo v1";

// Keep each task on a single line of the file.
std::string sanitize(std::string s) {
    std::replace(s.begin(), s.end(), '\n', ' ');
    std::replace(s.begin(), s.end(), '\r', ' ');
    return s;
}

}  // namespace

int TodoList::add(const std::string& text) {
    Task t;
    t.id = nextId_++;
    t.text = sanitize(text);
    tasks_.push_back(t);
    return t.id;
}

Task* TodoList::findMut(int id) {
    for (auto& t : tasks_)
        if (t.id == id) return &t;
    return nullptr;
}

std::optional<Task> TodoList::find(int id) const {
    for (const auto& t : tasks_)
        if (t.id == id) return t;
    return std::nullopt;
}

bool TodoList::complete(int id) {
    Task* t = findMut(id);
    if (!t) return false;
    t->done = true;
    return true;
}

bool TodoList::remove(int id) {
    auto it = std::find_if(tasks_.begin(), tasks_.end(),
                           [id](const Task& t) { return t.id == id; });
    if (it == tasks_.end()) return false;
    tasks_.erase(it);
    return true;
}

bool TodoList::edit(int id, const std::string& text) {
    Task* t = findMut(id);
    if (!t) return false;
    t->text = sanitize(text);
    return true;
}

void TodoList::save(std::ostream& out) const {
    out << kHeader << '\n';
    for (const auto& t : tasks_)
        out << t.id << '\t' << (t.done ? 1 : 0) << '\t' << t.text << '\n';
}

TodoList TodoList::load(std::istream& in) {
    TodoList list;
    std::string line;
    int lineNo = 0;
    while (std::getline(in, line)) {
        ++lineNo;
        if (line.empty() || line[0] == '#') continue;
        auto bad = [&] {
            return std::runtime_error("malformed task on line " + std::to_string(lineNo));
        };
        size_t a = line.find('\t');
        if (a == std::string::npos) throw bad();
        size_t b = line.find('\t', a + 1);
        if (b == std::string::npos) throw bad();
        Task t;
        try {
            size_t used = 0;
            t.id = std::stoi(line.substr(0, a), &used);
            if (used != a || t.id <= 0) throw bad();
        } catch (const std::logic_error&) {
            throw bad();
        }
        std::string done = line.substr(a + 1, b - a - 1);
        if (done != "0" && done != "1") throw bad();
        t.done = done == "1";
        t.text = line.substr(b + 1);
        if (list.findMut(t.id)) throw bad();
        list.tasks_.push_back(t);
        list.nextId_ = std::max(list.nextId_, t.id + 1);
    }
    return list;
}

TodoList TodoList::loadFile(const std::string& path) {
    std::ifstream in(path);
    if (!in) return TodoList{};
    return load(in);
}

void TodoList::saveFile(const std::string& path) const {
    std::ofstream out(path, std::ios::trunc);
    if (!out) throw std::runtime_error("cannot write " + path);
    save(out);
}

std::string format(const Task& t) {
    return std::string(t.done ? "[x] " : "[ ] ") + std::to_string(t.id) + "  " + t.text;
}

}  // namespace todo
