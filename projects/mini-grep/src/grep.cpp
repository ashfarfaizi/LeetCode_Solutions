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

bool isWordChar(char c) {
    return std::isalnum(static_cast<unsigned char>(c)) || c == '_';
}

}  // namespace

Matcher::Matcher(Options opts) : opts_(std::move(opts)) {
    needle_ = opts_.ignoreCase ? toLower(opts_.pattern) : opts_.pattern;
}

bool Matcher::contains(const std::string& hay) const {
    if (opts_.wholeLine) return hay == needle_;
    if (!opts_.wholeWord || needle_.empty()) return hay.find(needle_) != std::string::npos;
    for (std::size_t pos = hay.find(needle_); pos != std::string::npos;
         pos = hay.find(needle_, pos + 1)) {
        std::size_t end = pos + needle_.size();
        bool leftOk = pos == 0 || !isWordChar(hay[pos - 1]);
        bool rightOk = end == hay.size() || !isWordChar(hay[end]);
        if (leftOk && rightOk) return true;
    }
    return false;
}

bool Matcher::matches(const std::string& line) const {
    bool found = opts_.ignoreCase ? contains(toLower(line)) : contains(line);
    return found != opts_.invert;
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
