#pragma once
// Core of mini-grep: decide whether a line matches and scan whole streams.

#include <istream>
#include <cstddef>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

namespace mgrep {

struct Options {
    std::string pattern;
    bool ignoreCase = false;
    bool invert = false;       // select lines that do NOT match
    bool wholeWord = false;    // match only where bounded by non-word chars
    bool wholeLine = false;    // the entire line must equal the pattern
    bool lineNumbers = false;  // prefix matches with their 1-based line number
    bool countOnly = false;    // print only the number of matching lines
    bool onlyMatching = false; // print each matched part, not the whole line
    std::size_t maxCount = 0;  // stop after this many matching lines (0 = no limit)
};

class Matcher {
public:
    explicit Matcher(Options opts);

    // True if line is selected: it contains the pattern (as a whole word when
    // wholeWord is set), negated when invert is set.
    bool matches(const std::string& line) const;

    // Start/length of every non-overlapping occurrence of the pattern in line,
    // left to right, honouring ignoreCase, wholeWord and wholeLine (but not
    // invert). An empty pattern yields no spans.
    std::vector<std::pair<std::size_t, std::size_t>> spans(const std::string& line) const;

    const Options& options() const { return opts_; }

private:
    bool contains(const std::string& haystack) const;
    bool wordBounded(const std::string& hay, std::size_t pos) const;

    Options opts_;
    std::string needle_;  // pattern, lowercased when ignoreCase is set
};

// Reads in line by line and writes every matching line to out, prefixed with
// "label:" when label is non-empty and "N:" when lineNumbers is set. With
// onlyMatching (and not invert) each matched span is written on its own line
// with the same prefixes instead of the whole line. With
// countOnly, writes just "label:count" (or "count") instead. Reading stops
// once maxCount lines have matched (when maxCount > 0). Returns the number of
// matching lines.
std::size_t scan(std::istream& in, std::ostream& out, const Matcher& m,
                 const std::string& label = "");

// True if any line read from in is selected by m. Stops reading at the first
// selected line, which is what -l and -L need.
bool anyMatch(std::istream& in, const Matcher& m);

}  // namespace mgrep
