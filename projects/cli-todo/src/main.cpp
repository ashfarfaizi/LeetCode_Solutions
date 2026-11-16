// todo: command-line front end for the cli-todo library.
#include "todo.hpp"

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

namespace {

int usage() {
    std::cerr << "usage: todo [-f FILE] add [-p LEVEL] TEXT...\n"
                 "       todo [-f FILE] list [--pending | --done]\n"
                 "       todo [-f FILE] done ID\n"
                 "       todo [-f FILE] rm ID\n"
                 "       todo [-f FILE] edit ID TEXT...\n"
                 "       todo [-f FILE] pri ID LEVEL\n"
                 "       todo [-f FILE] clear\n"
                 "LEVEL is high, normal or low (or h, n, l)\n";
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
            if (i < args.size()) {
                if (args[i] == "--pending") show = Pending;
                else if (args[i] == "--done") show = Done;
                else return usage();
                ++i;
            }
            if (i != args.size()) return usage();
            for (const auto& t : list.sorted()) {
                if ((show == Pending && t.done) || (show == Done && !t.done)) continue;
                std::cout << todo::format(t) << '\n';
            }
        } else if (cmd == "clear") {
            if (i != args.size()) return usage();
            int n = list.clearDone();
            if (n > 0) list.saveFile(path);
            std::cout << "cleared " << n << (n == 1 ? " task\n" : " tasks\n");
        } else if (cmd == "done" || cmd == "rm") {
            int id = 0;
            if (i + 1 != args.size() || !parseId(args[i], id)) return usage();
            bool ok = cmd == "done" ? list.complete(id) : list.remove(id);
            if (!ok) return noTask(id);
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
