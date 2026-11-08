#pragma once
// Core of mini-grep: decide whether a line matches and scan whole streams.

#include <istream>
#include <cstddef>
#include <ostream>
#include <string>

namespace mgrep {

struct Options {
    std::string pattern;
    bool ignoreCase = false;
    bool invert = false;       // select lines that do NOT match
    bool wholeWord = false;    // match only where bounded by non-word chars
    bool wholeLine = false;    // the entire line must equal the pattern
    bool lineNumbers = false;  // prefix matches with their 1-based line number
    bool countOnly = false;    // print only the number of matching lines
    std::size_t maxCount = 0;  // stop after this many matching lines (0 = no limit)
};

class Matcher {
public:
    explicit Matcher(Options opts);

    // True if line is selected: it contains the pattern (as a whole word when
    // wholeWord is set), negated when invert is set.
    bool matches(const std::string& line) const;

    const Options& options() const { return opts_; }

private:
    bool contains(const std::string& haystack) const;

    Options opts_;
    std::string needle_;  // pattern, lowercased when ignoreCase is set
};

// Reads in line by line and writes every matching line to out, prefixed with
// "label:" when label is non-empty and "N:" when lineNumbers is set. With
// countOnly, writes just "label:count" (or "count") instead. Reading stops
// once maxCount lines have matched (when maxCount > 0). Returns the number of
// matching lines.
std::size_t scan(std::istream& in, std::ostream& out, const Matcher& m,
                 const std::string& label = "");

}  // namespace mgrep
