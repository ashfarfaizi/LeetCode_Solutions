#pragma once
// Core of mini-grep: decide whether a line matches and scan whole streams.

#include <istream>
#include <ostream>
#include <string>

namespace mgrep {

struct Options {
    std::string pattern;
    bool ignoreCase = false;
};

class Matcher {
public:
    explicit Matcher(Options opts);

    // True if line contains the pattern under the configured options.
    bool matches(const std::string& line) const;

    const Options& options() const { return opts_; }

private:
    Options opts_;
    std::string needle_;  // pattern, lowercased when ignoreCase is set
};

// Reads in line by line and writes every matching line to out, prefixed with
// "label:" when label is non-empty. Returns the number of matching lines.
std::size_t scan(std::istream& in, std::ostream& out, const Matcher& m,
                 const std::string& label = "");

}  // namespace mgrep
