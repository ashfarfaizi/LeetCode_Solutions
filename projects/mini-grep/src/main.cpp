// mgrep: print lines that contain a pattern.
//
//   mgrep [-icnvwx] [-m NUM] PATTERN [FILE...]
//
// With no FILE (or FILE "-") standard input is read. When more than one file
// is given each output line is prefixed with its file name.
// Exit status: 0 if any line matched, 1 if none did, 2 on usage or I/O error.

#include "grep.hpp"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace {

void usage() { std::cerr << "usage: mgrep [-icnvwx] [-m NUM] PATTERN [FILE...]\n"; }

// Parses a non-negative decimal count; returns false on anything else.
bool parseCount(const std::string& s, std::size_t& out) {
    if (s.empty() || s.find_first_not_of("0123456789") != std::string::npos) return false;
    out = std::strtoull(s.c_str(), nullptr, 10);
    return true;
}

}  // namespace

int main(int argc, char** argv) {
    mgrep::Options opts;
    int i = 1;
    for (; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--") {
            ++i;
            break;
        }
        if (arg.size() < 2 || arg[0] != '-') break;
        for (std::size_t j = 1; j < arg.size(); ++j) {
            switch (arg[j]) {
                case 'i': opts.ignoreCase = true; break;
                case 'n': opts.lineNumbers = true; break;
                case 'c': opts.countOnly = true; break;
                case 'v': opts.invert = true; break;
                case 'w': opts.wholeWord = true; break;
                case 'x': opts.wholeLine = true; break;
                case 'm': {
                    // The count is the rest of this argument (-m3) or the next one (-m 3).
                    std::string value = arg.substr(j + 1);
                    if (value.empty() && i + 1 < argc) value = argv[++i];
                    if (!parseCount(value, opts.maxCount) || opts.maxCount == 0) {
                        std::cerr << "mgrep: -m needs a positive number\n";
                        usage();
                        return 2;
                    }
                    j = arg.size();  // the value consumed the rest of the argument
                    break;
                }
                default:
                    std::cerr << "mgrep: unknown option -" << arg[j] << '\n';
                    usage();
                    return 2;
            }
        }
    }
    if (i >= argc) {
        usage();
        return 2;
    }
    opts.pattern = argv[i++];
    std::vector<std::string> files(argv + i, argv + argc);
    if (files.empty()) files.push_back("-");

    mgrep::Matcher matcher(opts);
    bool showNames = files.size() > 1;
    bool anyMatch = false, hadError = false;
    for (const std::string& name : files) {
        std::string label = showNames ? (name == "-" ? "(standard input)" : name) : "";
        if (name == "-") {
            anyMatch |= mgrep::scan(std::cin, std::cout, matcher, label) > 0;
            continue;
        }
        std::ifstream file(name);
        if (!file) {
            std::cerr << "mgrep: " << name << ": cannot open file\n";
            hadError = true;
            continue;
        }
        anyMatch |= mgrep::scan(file, std::cout, matcher, label) > 0;
    }
    if (hadError) return 2;
    return anyMatch ? 0 : 1;
}
