// mgrep: print lines that contain a pattern.
//
//   mgrep [-bicnovwxlLqrsHh] [-m NUM] [-A NUM] [-B NUM] [-C NUM]
//         {PATTERN | -e PATTERN... | -f FILE...} [FILE...]
//
// With no FILE (or FILE "-") standard input is read. When more than one file
// is given each output line is prefixed with its file name (-H forces the
// prefix, -h suppresses it). -l / -L print
// only the names of files that do / do not contain a selected line, and -q
// prints nothing at all, exiting 0 at the first selected line.
// -s hides "cannot open" messages (the exit status still reports them).
// -r searches directories recursively (the current directory when no FILE is
// given); without it a directory argument is reported as an error.
// -f FILE reads one pattern per line from FILE ("-" for standard input).
// Exit status: 0 if any line matched, 1 if none did, 2 on usage or I/O error.

#include "grep.hpp"

#include <algorithm>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace {

enum class ListMode { None, WithMatch, WithoutMatch };

void usage() {
    std::cerr << "usage: mgrep [-bicnovwxlLqrsHh] [-m NUM] [-A NUM] [-B NUM] [-C NUM]\n"
                 "             {PATTERN | -e PATTERN... | -f FILE...} [FILE...]\n";
}

// Parses a non-negative decimal count; returns false on anything else.
bool parseCount(const std::string& s, std::size_t& out) {
    if (s.empty() || s.find_first_not_of("0123456789") != std::string::npos) return false;
    out = std::strtoull(s.c_str(), nullptr, 10);
    return true;
}

// Appends every line of the named file ("-" = standard input) to patterns,
// dropping a trailing '\r' so files with CRLF endings work. Returns false if
// the file cannot be opened.
bool readPatternFile(const std::string& name, std::vector<std::string>& patterns) {
    std::ifstream file;
    if (name != "-") {
        file.open(name);
        if (!file) return false;
    }
    std::istream& in = name == "-" ? std::cin : file;
    std::string line;
    while (std::getline(in, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        patterns.push_back(line);
    }
    return true;
}

// Appends name to out, or with recursive and a directory, every regular file
// below it in sorted order (so output is deterministic). Unreadable
// subdirectories are skipped.
void expand(const std::string& name, bool recursive, std::vector<std::string>& out) {
    namespace fs = std::filesystem;
    std::error_code ec;
    if (!recursive || name == "-" || !fs::is_directory(name, ec)) {
        out.push_back(name);
        return;
    }
    std::vector<std::string> found;
    for (fs::recursive_directory_iterator it(name, fs::directory_options::skip_permission_denied, ec), end;
         !ec && it != end; it.increment(ec)) {
        if (it->is_regular_file(ec)) found.push_back(it->path().string());
    }
    std::sort(found.begin(), found.end());
    out.insert(out.end(), found.begin(), found.end());
}

}  // namespace

int main(int argc, char** argv) {
    mgrep::Options opts;
    ListMode list = ListMode::None;
    bool quiet = false;
    bool noMessages = false;  // -s
    bool recursive = false;   // -r
    enum class Names { Auto, Always, Never } names = Names::Auto;
    std::vector<std::string> patterns;  // from -e and -f
    bool patternOption = false;         // -e or -f given: no positional pattern
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
                case 'b': opts.byteOffset = true; break;
                case 'c': opts.countOnly = true; break;
                case 'v': opts.invert = true; break;
                case 'w': opts.wholeWord = true; break;
                case 'x': opts.wholeLine = true; break;
                case 'o': opts.onlyMatching = true; break;
                case 'l': list = ListMode::WithMatch; break;
                case 'L': list = ListMode::WithoutMatch; break;
                case 'q': quiet = true; break;
                case 's': noMessages = true; break;
                case 'r': recursive = true; break;
                case 'H': names = Names::Always; break;
                case 'h': names = Names::Never; break;
                case 'e':
                case 'f': {
                    // Like -m, the value is the rest of the argument or the next one.
                    const char opt = arg[j];
                    std::string value;
                    if (j + 1 < arg.size()) {
                        value = arg.substr(j + 1);
                    } else if (i + 1 < argc) {
                        value = argv[++i];
                    } else {
                        std::cerr << "mgrep: -" << opt << " needs "
                                  << (opt == 'e' ? "a pattern" : "a file") << '\n';
                        usage();
                        return 2;
                    }
                    if (opt == 'e') {
                        patterns.push_back(value);
                    } else if (!readPatternFile(value, patterns)) {
                        std::cerr << "mgrep: " << value << ": cannot open pattern file\n";
                        return 2;
                    }
                    patternOption = true;
                    j = arg.size();
                    break;
                }
                case 'm':
                case 'A':
                case 'B':
                case 'C': {
                    // The count is the rest of this argument (-m3) or the next one (-m 3).
                    const char opt = arg[j];
                    std::string value = arg.substr(j + 1);
                    if (value.empty() && i + 1 < argc) value = argv[++i];
                    std::size_t n = 0;
                    bool ok = parseCount(value, n);
                    if (opt == 'm') {
                        ok = ok && n > 0;
                        opts.maxCount = n;
                    } else {
                        if (opt != 'B') opts.afterContext = n;
                        if (opt != 'A') opts.beforeContext = n;
                    }
                    if (!ok) {
                        std::cerr << "mgrep: -" << opt << " needs a "
                                  << (opt == 'm' ? "positive" : "non-negative") << " number\n";
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
    if (!patternOption) {
        if (i >= argc) {
            usage();
            return 2;
        }
        patterns.push_back(argv[i++]);
    }
    if (patterns.empty()) {
        opts.noPatterns = true;  // -f of an empty file matches nothing
    } else {
        opts.pattern = patterns.front();
        opts.morePatterns.assign(patterns.begin() + 1, patterns.end());
    }
    std::vector<std::string> args(argv + i, argv + argc);
    if (args.empty()) args.push_back(recursive ? "." : "-");
    std::vector<std::string> files;
    for (const std::string& a : args) expand(a, recursive, files);

    mgrep::Matcher matcher(opts);
    // With -r names are shown by default even if only one file turned up.
    bool showNames = names == Names::Auto ? files.size() > 1 || recursive
                                          : names == Names::Always;
    bool anyMatch = false, hadError = false;
    for (const std::string& name : files) {
        std::string label = showNames ? (name == "-" ? "(standard input)" : name) : "";
        std::ifstream file;
        if (name != "-") {
            std::error_code ec;
            if (std::filesystem::is_directory(name, ec)) {
                if (!noMessages) std::cerr << "mgrep: " << name << ": is a directory\n";
                hadError = true;
                continue;
            }
            file.open(name);
            if (!file) {
                if (!noMessages) std::cerr << "mgrep: " << name << ": cannot open file\n";
                hadError = true;
                continue;
            }
        }
        std::istream& in = name == "-" ? std::cin : file;
        if (quiet) {
            // A match settles the answer, so skip the remaining files (even
            // after an earlier open error, like grep -q).
            if (mgrep::anyMatch(in, matcher)) return 0;
            continue;
        }
        if (list != ListMode::None) {
            // -l succeeds when some file matched, -L when some file did not.
            bool found = mgrep::anyMatch(in, matcher);
            if (found == (list == ListMode::WithMatch)) {
                std::cout << (name == "-" ? "(standard input)" : name) << '\n';
                anyMatch = true;
            }
            continue;
        }
        anyMatch |= mgrep::scan(in, std::cout, matcher, label) > 0;
    }
    if (hadError) return 2;
    return anyMatch ? 0 : 1;
}
