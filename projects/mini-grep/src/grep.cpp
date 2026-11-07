#include "grep.hpp"

#include <algorithm>
#include <cctype>
#include <utility>

namespace mgrep {

namespace {

std::string toLower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    return s;
}

}  // namespace

Matcher::Matcher(Options opts) : opts_(std::move(opts)) {
    needle_ = opts_.ignoreCase ? toLower(opts_.pattern) : opts_.pattern;
}

bool Matcher::matches(const std::string& line) const {
    if (opts_.ignoreCase) return toLower(line).find(needle_) != std::string::npos;
    return line.find(needle_) != std::string::npos;
}

std::size_t scan(std::istream& in, std::ostream& out, const Matcher& m,
                 const std::string& label) {
    const Options& o = m.options();
    std::size_t matched = 0, lineNo = 0;
    std::string line;
    while (std::getline(in, line)) {
        ++lineNo;
        if (!m.matches(line)) continue;
        ++matched;
        if (o.countOnly) continue;
        if (!label.empty()) out << label << ':';
        if (o.lineNumbers) out << lineNo << ':';
        out << line << '\n';
    }
    if (o.countOnly) {
        if (!label.empty()) out << label << ':';
        out << matched << '\n';
    }
    return matched;
}

}  // namespace mgrep
