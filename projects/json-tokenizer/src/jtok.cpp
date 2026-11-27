// jtok: print the tokens of a JSON document, or just check that it is valid.
//
//   jtok [--comments] [--check | --minify | --pretty[=N] | --stats] [FILE]
//
// Reads FILE, or standard input when it is omitted or "-".
//
// Exit status: 0 = ok, 1 = invalid JSON, 2 = usage or I/O error.

#include "json_comments.hpp"
#include "json_format.hpp"
#include "json_stats.hpp"
#include "json_tokenizer.hpp"
#include "json_validate.hpp"

#include <cstdio>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>

namespace {

void usage(std::FILE* out) {
    std::fprintf(out,
                 "usage: jtok [--comments] [--check | --minify | --pretty[=N] | --stats] [FILE]\n"
                 "  Prints one token per line as LINE:COL TYPE VALUE.\n"
                 "  --check       only validate; print nothing on success\n"
                 "  --minify      print the document without insignificant whitespace\n"
                 "  --pretty[=N]  print the document indented by N spaces (default 2)\n"
                 "  --stats       print counts of each kind of value and the maximum depth\n"
                 "  --comments    allow // and /* */ comments (JSONC); they are dropped\n"
                 "  -h, --help\n");
}

}  // namespace

int main(int argc, char** argv) {
    enum class Mode { Tokens, Check, Minify, Pretty, Stats };
    Mode mode = Mode::Tokens;
    unsigned indent = 2;
    bool allow_comments = false;
    auto set_mode = [&](Mode m, const std::string& arg) {
        if (mode != Mode::Tokens && mode != m) {
            std::fprintf(stderr, "jtok: '%s' conflicts with an earlier mode option\n", arg.c_str());
            return false;
        }
        mode = m;
        return true;
    };
    std::string path = "-";
    bool have_path = false;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--check" || arg == "--minify" || arg == "--pretty" || arg == "--stats") {
            Mode m = arg == "--check"    ? Mode::Check
                     : arg == "--minify" ? Mode::Minify
                     : arg == "--stats"  ? Mode::Stats
                                         : Mode::Pretty;
            if (!set_mode(m, arg)) return 2;
        } else if (arg == "--comments") {
            allow_comments = true;
        } else if (arg.rfind("--pretty=", 0) == 0) {
            std::string n = arg.substr(9);
            if (n.empty() || n.size() > 2 || n.find_first_not_of("0123456789") != std::string::npos) {
                std::fprintf(stderr, "jtok: invalid indent '%s' (expected 0-99)\n", n.c_str());
                return 2;
            }
            indent = static_cast<unsigned>(std::stoul(n));
            if (!set_mode(Mode::Pretty, arg)) return 2;
        } else if (arg == "-h" || arg == "--help") {
            usage(stdout);
            return 0;
        } else if (arg.size() > 1 && arg[0] == '-') {
            std::fprintf(stderr, "jtok: unknown option '%s'\n", arg.c_str());
            usage(stderr);
            return 2;
        } else if (have_path) {
            std::fprintf(stderr, "jtok: only one input file is supported\n");
            return 2;
        } else {
            path = arg;
            have_path = true;
        }
    }

    std::string text;
    if (path == "-") {
        text.assign(std::istreambuf_iterator<char>(std::cin), std::istreambuf_iterator<char>());
    } else {
        std::ifstream in(path, std::ios::binary);
        if (!in) {
            std::fprintf(stderr, "jtok: cannot open '%s'\n", path.c_str());
            return 2;
        }
        std::ostringstream ss;
        ss << in.rdbuf();
        text = ss.str();
    }
    const char* name = path == "-" ? "<stdin>" : path.c_str();

    try {
        if (allow_comments) text = jt::strip_comments(text);
        if (mode == Mode::Minify) {
            std::printf("%s\n", jt::minify(text).c_str());
            return 0;
        }
        if (mode == Mode::Pretty) {
            std::printf("%s\n", jt::pretty(text, indent).c_str());
            return 0;
        }
        if (mode == Mode::Stats) {
            jt::Stats st = jt::stats(text);
            std::printf("objects   %zu\narrays    %zu\nkeys      %zu\nstrings   %zu\n"
                        "numbers   %zu\nbooleans  %zu\nnulls     %zu\nmax_depth %zu\n",
                        st.objects, st.arrays, st.keys, st.strings, st.numbers, st.booleans,
                        st.nulls, st.max_depth);
            return 0;
        }
        jt::validate(text);
        if (mode == Mode::Check) return 0;
        jt::Tokenizer lexer(text);
        for (auto tok = lexer.next(); tok.type != jt::TokenType::End; tok = lexer.next()) {
            std::string value = jt::token_text(tok);
            std::printf("%zu:%zu %s %s\n", tok.line, tok.column, jt::type_name(tok.type), value.c_str());
        }
    } catch (const jt::TokenizeError& e) {
        std::fprintf(stderr, "%s:%zu:%zu: error: %s\n", name, e.line(), e.column(), e.what());
        return 1;
    }
    return 0;
}
