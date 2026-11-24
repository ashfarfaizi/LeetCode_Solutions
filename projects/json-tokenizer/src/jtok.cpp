// jtok: print the tokens of a JSON document, or just check that it is valid.
//
//   jtok [--check] [FILE]     reads FILE, or standard input when omitted or "-"
//
// Exit status: 0 = ok, 1 = invalid JSON, 2 = usage or I/O error.

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
                 "usage: jtok [--check] [FILE]\n"
                 "  Prints one token per line as LINE:COL TYPE VALUE.\n"
                 "  --check   only validate; print nothing on success\n"
                 "  -h, --help\n");
}

// Escapes a decoded string value so each token stays on one line.
std::string quoted(const std::string& s) {
    std::string out = "\"";
    for (unsigned char c : s) {
        switch (c) {
            case '"': out += "\\\""; break;
            case '\\': out += "\\\\"; break;
            case '\n': out += "\\n"; break;
            case '\r': out += "\\r"; break;
            case '\t': out += "\\t"; break;
            default:
                if (c < 0x20) {
                    char buf[8];
                    std::snprintf(buf, sizeof buf, "\\u%04x", c);
                    out += buf;
                } else {
                    out += static_cast<char>(c);
                }
        }
    }
    return out + "\"";
}

}  // namespace

int main(int argc, char** argv) {
    bool check_only = false;
    std::string path = "-";
    bool have_path = false;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--check") {
            check_only = true;
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
        jt::validate(text);
        if (check_only) return 0;
        jt::Tokenizer lexer(text);
        for (auto tok = lexer.next(); tok.type != jt::TokenType::End; tok = lexer.next()) {
            std::string value = tok.type == jt::TokenType::String ? quoted(tok.value) : tok.value;
            std::printf("%zu:%zu %s %s\n", tok.line, tok.column, jt::type_name(tok.type), value.c_str());
        }
    } catch (const jt::TokenizeError& e) {
        std::fprintf(stderr, "%s:%zu:%zu: error: %s\n", name, e.line(), e.column(), e.what());
        return 1;
    }
    return 0;
}
