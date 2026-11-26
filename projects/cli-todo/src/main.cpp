// todo: command-line front end for the cli-todo library.
#include "todo.hpp"

#include <cstdlib>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

namespace {

const char* const kUsage =
    "usage: todo [-f FILE] add [-p LEVEL] TEXT...\n"
    "       todo [-f FILE] list [--pending | --done] [-p LEVEL]\n"
    "       todo [-f FILE] done ID...\n"
    "       todo [-f FILE] undo ID...\n"
    "       todo [-f FILE] rm ID...\n"
    "       todo [-f FILE] edit ID TEXT...\n"
    "       todo [-f FILE] pri ID LEVEL\n"
    "       todo [-f FILE] find TEXT...\n"
    "       todo [-f FILE] next\n"
    "       todo [-f FILE] stats\n"
    "       todo [-f FILE] clear\n"
    "       todo [-f FILE] export --md\n"
    "       todo help\n"
    "LEVEL is high, normal or low (or h, n, l)\n";

int usage() {
    std::cerr << kUsage;
    return 2;
}

int noTask(int id) {
    std::cerr << "todo: no task " << id << '\n';
    return 1;
}

bool parseId(const std::string& s, int& id) {
    if (s.empty() || s.find_first_not_of("0123456789") != std::string::npos) return false;
    try {
        id = std::stoi(s);
    } catch (const std::out_of_range&) {
        return false;
    }
    return id > 0;
}

std::string joinArgs(const std::vector<std::string>& args, size_t from) {
    std::string out;
    for (size_t i = from; i < args.size(); ++i) {
        if (!out.empty()) out += ' ';
        out += args[i];
    }
    return out;
}

}  // namespace

int main(int argc, char** argv) {
    std::vector<std::string> args(argv + 1, argv + argc);
    if (!args.empty() && (args[0] == "help" || args[0] == "--help" || args[0] == "-h")) {
        std::cout << kUsage;
        return 0;
    }
    std::string path = "todo.txt";
    if (const char* env = std::getenv("TODO_FILE")) path = env;
    size_t i = 0;
    if (i < args.size() && args[i] == "-f") {
        if (i + 1 >= args.size()) return usage();
        path = args[i + 1];
        i += 2;
    }
    if (i >= args.size()) return usage();
    const std::string cmd = args[i++];

    try {
        todo::TodoList list = todo::TodoList::loadFile(path);
        if (cmd == "add") {
            todo::Priority prio = todo::Priority::Normal;
            if (i < args.size() && args[i] == "-p") {
                if (i + 1 >= args.size()) return usage();
                auto p = todo::parsePriority(args[i + 1]);
                if (!p) return usage();
                prio = *p;
                i += 2;
            }
            std::string text = joinArgs(args, i);
            if (text.empty()) return usage();
            int id = list.add(text, prio);
            list.saveFile(path);
            std::cout << "added " << id << '\n';
        } else if (cmd == "list") {
            enum { All, Pending, Done } show = All;
            std::optional<todo::Priority> only;
            for (; i < args.size(); ++i) {
                if (args[i] == "--pending" && show == All) {
                    show = Pending;
                } else if (args[i] == "--done" && show == All) {
                    show = Done;
                } else if (args[i] == "-p" && !only && i + 1 < args.size()) {
                    only = todo::parsePriority(args[++i]);
                    if (!only) return usage();
                } else {
                    return usage();
                }
            }
            for (const auto& t : list.sorted()) {
                if ((show == Pending && t.done) || (show == Done && !t.done)) continue;
                if (only && t.priority != *only) continue;
                std::cout << todo::format(t) << '\n';
            }
        } else if (cmd == "find") {
            std::string needle = joinArgs(args, i);
            if (needle.empty()) return usage();
            auto hits = list.search(needle);
            for (const auto& t : hits) std::cout << todo::format(t) << '\n';
            if (hits.empty()) return 1;
        } else if (cmd == "export") {
            if (i + 1 != args.size() || args[i] != "--md") return usage();
            std::cout << todo::toMarkdown(list);
        } else if (cmd == "next") {
            if (i != args.size()) return usage();
            auto t = list.nextPending();
            if (!t) {
                std::cout << "nothing to do\n";
                return 1;
            }
            std::cout << todo::format(*t) << '\n';
        } else if (cmd == "stats") {
            if (i != args.size()) return usage();
            const todo::Stats s = list.stats();
            const int pct = s.total ? s.done * 100 / s.total : 0;
            std::cout << s.total << " tasks, " << s.done << " done (" << pct << "%), "
                      << s.pending << " pending\n";
            if (s.pending > 0) {
                std::cout << "pending: " << s.pendingByPriority[2] << " high, "
                          << s.pendingByPriority[1] << " normal, "
                          << s.pendingByPriority[0] << " low\n";
            }
        } else if (cmd == "clear") {
            if (i != args.size()) return usage();
            int n = list.clearDone();
            if (n > 0) list.saveFile(path);
            std::cout << "cleared " << n << (n == 1 ? " task\n" : " tasks\n");
        } else if (cmd == "done" || cmd == "undo" || cmd == "rm") {
            // Several ids may be given; all are validated before any change.
            if (i >= args.size()) return usage();
            std::vector<int> ids;
            for (; i < args.size(); ++i) {
                int id = 0;
                if (!parseId(args[i], id)) return usage();
                ids.push_back(id);
            }
            for (int id : ids)
                if (!list.find(id)) return noTask(id);
            for (int id : ids) {
                if (cmd == "done") list.complete(id);
                else if (cmd == "undo") list.reopen(id);
                else list.remove(id);
            }
            list.saveFile(path);
        } else if (cmd == "edit") {
            int id = 0;
            if (i >= args.size() || !parseId(args[i], id)) return usage();
            std::string text = joinArgs(args, i + 1);
            if (text.empty()) return usage();
            if (!list.edit(id, text)) return noTask(id);
            list.saveFile(path);
        } else if (cmd == "pri") {
            int id = 0;
            if (i + 2 != args.size() || !parseId(args[i], id)) return usage();
            auto p = todo::parsePriority(args[i + 1]);
            if (!p) return usage();
            if (!list.setPriority(id, *p)) return noTask(id);
            list.saveFile(path);
        } else {
            return usage();
        }
    } catch (const std::exception& e) {
        std::cerr << "todo: " << path << ": " << e.what() << '\n';
        return 1;
    }
    return 0;
}
