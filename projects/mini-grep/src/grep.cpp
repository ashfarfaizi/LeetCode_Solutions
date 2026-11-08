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
        if (wordBounded(hay, pos)) return true;
    }
    return false;
}

bool Matcher::wordBounded(const std::string& hay, std::size_t pos) const {
    std::size_t end = pos + needle_.size();
    bool leftOk = pos == 0 || !isWordChar(hay[pos - 1]);
    bool rightOk = end == hay.size() || !isWordChar(hay[end]);
    return leftOk && rightOk;
}

std::vector<std::pair<std::size_t, std::size_t>> Matcher::spans(const std::string& line) const {
    std::vector<std::pair<std::size_t, std::size_t>> out;
    if (needle_.empty()) return out;
    const std::string hay = opts_.ignoreCase ? toLower(line) : line;
    if (opts_.wholeLine) {
        if (hay == needle_) out.emplace_back(0, hay.size());
        return out;
    }
    std::size_t pos = hay.find(needle_);
    while (pos != std::string::npos) {
        if (!opts_.wholeWord || wordBounded(hay, pos)) {
            out.emplace_back(pos, needle_.size());
            pos = hay.find(needle_, pos + needle_.size());
        } else {
            pos = hay.find(needle_, pos + 1);
        }
    }
    return out;
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
    while ((o.maxCount == 0 || matched < o.maxCount) && std::getline(in, line)) {
        ++lineNo;
        if (!m.matches(line)) continue;
        ++matched;
        if (o.countOnly) continue;
        if (o.onlyMatching) {
            if (o.invert) continue;  // an unmatched line has no parts to print
            for (const auto& [start, len] : m.spans(line)) {
                if (!label.empty()) out << label << ':';
                if (o.lineNumbers) out << lineNo << ':';
                out << line.substr(start, len) << '\n';
            }
            continue;
        }
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

bool anyMatch(std::istream& in, const Matcher& m) {
    std::string line;
    while (std::getline(in, line)) {
        if (m.matches(line)) return true;
    }
    return false;
}

}  // namespace mgrep
