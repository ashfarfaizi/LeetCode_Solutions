#include "todo.hpp"

#include <algorithm>
#include <cctype>
#include <cstdio>
#include <fstream>
#include <istream>
#include <ostream>
#include <stdexcept>
#include <string>

namespace todo {

namespace {

const char* const kHeaderV1 = "# cli-todo v1";
const char* const kHeaderV2 = "# cli-todo v2";
const std::string kNextIdPrefix = "# next-id ";

char priorityCode(Priority p) {
    switch (p) {
        case Priority::Low: return 'L';
        case Priority::High: return 'H';
        default: return 'N';
    }
}

// Keep each task on a single line of the file.
std::string sanitize(std::string s) {
    std::replace(s.begin(), s.end(), '\n', ' ');
    std::replace(s.begin(), s.end(), '\r', ' ');
    return s;
}

}  // namespace

std::optional<Priority> parsePriority(const std::string& s) {
    if (s == "low" || s == "l") return Priority::Low;
    if (s == "normal" || s == "n") return Priority::Normal;
    if (s == "high" || s == "h") return Priority::High;
    return std::nullopt;
}

const char* priorityName(Priority p) {
    switch (p) {
        case Priority::Low: return "low";
        case Priority::High: return "high";
        default: return "normal";
    }
}

int TodoList::add(const std::string& text, Priority p) {
    Task t;
    t.id = nextId_++;
    t.text = sanitize(text);
    t.priority = p;
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

bool TodoList::reopen(int id) {
    Task* t = findMut(id);
    if (!t) return false;
    t->done = false;
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

bool TodoList::setPriority(int id, Priority p) {
    Task* t = findMut(id);
    if (!t) return false;
    t->priority = p;
    return true;
}

int TodoList::clearDone() {
    auto before = tasks_.size();
    tasks_.erase(std::remove_if(tasks_.begin(), tasks_.end(),
                                [](const Task& t) { return t.done; }),
                 tasks_.end());
    return static_cast<int>(before - tasks_.size());
}

std::vector<Task> TodoList::sorted() const {
    std::vector<Task> out = tasks_;
    std::stable_sort(out.begin(), out.end(), [](const Task& a, const Task& b) {
        if (a.priority != b.priority) return a.priority > b.priority;
        return a.id < b.id;
    });
    return out;
}

std::vector<Task> TodoList::search(const std::string& needle) const {
    auto lower = [](std::string s) {
        for (char& c : s) c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
        return s;
    };
    const std::string n = lower(needle);
    std::vector<Task> out;
    for (const auto& t : sorted())
        if (lower(t.text).find(n) != std::string::npos) out.push_back(t);
    return out;
}

std::optional<Task> TodoList::nextPending() const {
    const Task* best = nullptr;
    for (const auto& t : tasks_) {
        if (t.done) continue;
        if (!best || t.priority > best->priority ||
            (t.priority == best->priority && t.id < best->id))
            best = &t;
    }
    if (!best) return std::nullopt;
    return *best;
}

Stats TodoList::stats() const {
    Stats s;
    for (const auto& t : tasks_) {
        ++s.total;
        if (t.done) {
            ++s.done;
        } else {
            ++s.pending;
            ++s.pendingByPriority[static_cast<int>(t.priority)];
        }
    }
    return s;
}

void TodoList::save(std::ostream& out) const {
    out << kHeaderV2 << '\n';
    // Remember the id counter so ids of removed or cleared tasks are not
    // handed out again after a reload. Older readers skip it as a comment.
    out << kNextIdPrefix << nextId_ << '\n';
    for (const auto& t : tasks_)
        out << t.id << '\t' << (t.done ? 1 : 0) << '\t' << priorityCode(t.priority) << '\t'
            << t.text << '\n';
}

TodoList TodoList::load(std::istream& in) {
    TodoList list;
    std::string line;
    int lineNo = 0;
    int version = 1;
    while (std::getline(in, line)) {
        ++lineNo;
        if (line == kHeaderV2) version = 2;
        if (line == kHeaderV1) version = 1;
        if (line.compare(0, kNextIdPrefix.size(), kNextIdPrefix) == 0) {
            // Ignore an unparsable counter: ids are still derived from tasks.
            try {
                int n = std::stoi(line.substr(kNextIdPrefix.size()));
                if (n > 0) list.nextId_ = std::max(list.nextId_, n);
            } catch (const std::logic_error&) {
            }
            continue;
        }
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
        if (version >= 2) {
            size_t c = line.find('\t', b + 1);
            if (c != b + 2) throw bad();
            switch (line[b + 1]) {
                case 'L': t.priority = Priority::Low; break;
                case 'N': t.priority = Priority::Normal; break;
                case 'H': t.priority = Priority::High; break;
                default: throw bad();
            }
            b = c;
        }
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
    // Write to a sibling temp file and rename it over the target, so an
    // interrupted save never leaves a truncated or half-written list behind.
    const std::string tmp = path + ".tmp";
    {
        std::ofstream out(tmp, std::ios::trunc);
        if (!out) throw std::runtime_error("cannot write " + tmp);
        save(out);
        out.flush();
        if (!out) {
            std::remove(tmp.c_str());
            throw std::runtime_error("error writing " + tmp);
        }
    }
    if (std::rename(tmp.c_str(), path.c_str()) != 0) {
        std::remove(tmp.c_str());
        throw std::runtime_error("cannot replace " + path);
    }
}

std::string format(const Task& t) {
    std::string out = std::string(t.done ? "[x] " : "[ ] ") + std::to_string(t.id) + "  ";
    if (t.priority != Priority::Normal) out += std::string("(") + priorityName(t.priority) + ") ";
    return out + t.text;
}

}  // namespace todo
