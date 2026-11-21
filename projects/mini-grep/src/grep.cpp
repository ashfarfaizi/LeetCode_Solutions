#include "grep.hpp"

#include <algorithm>
#include <cctype>
#include <deque>
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
    needles_.push_back(opts_.pattern);
    needles_.insert(needles_.end(), opts_.morePatterns.begin(), opts_.morePatterns.end());
    if (opts_.ignoreCase) {
        for (std::string& n : needles_) n = toLower(n);
    }
}

bool Matcher::wordBounded(const std::string& hay, std::size_t pos, std::size_t len) {
    std::size_t end = pos + len;
    bool leftOk = pos == 0 || !isWordChar(hay[pos - 1]);
    bool rightOk = end == hay.size() || !isWordChar(hay[end]);
    return leftOk && rightOk;
}

std::size_t Matcher::findFrom(const std::string& hay, const std::string& needle,
                              std::size_t from) const {
    for (std::size_t pos = hay.find(needle, from); pos != std::string::npos;
         pos = hay.find(needle, pos + 1)) {
        if (!opts_.wholeWord || wordBounded(hay, pos, needle.size())) return pos;
    }
    return std::string::npos;
}

bool Matcher::contains(const std::string& hay, const std::string& needle) const {
    if (opts_.wholeLine) return hay == needle;
    if (needle.empty()) return true;
    return findFrom(hay, needle, 0) != std::string::npos;
}

std::vector<std::pair<std::size_t, std::size_t>> Matcher::spans(const std::string& line) const {
    std::vector<std::pair<std::size_t, std::size_t>> out;
    const std::string hay = opts_.ignoreCase ? toLower(line) : line;
    if (opts_.wholeLine) {
        for (const std::string& n : needles_) {
            if (!n.empty() && hay == n) {
                out.emplace_back(0, hay.size());
                break;
            }
        }
        return out;
    }
    std::size_t from = 0;
    while (from < hay.size()) {
        std::size_t bestPos = std::string::npos, bestLen = 0;
        for (const std::string& n : needles_) {
            if (n.empty()) continue;
            std::size_t pos = findFrom(hay, n, from);
            if (pos == std::string::npos) continue;
            if (pos < bestPos || (pos == bestPos && n.size() > bestLen)) {
                bestPos = pos;
                bestLen = n.size();
            }
        }
        if (bestPos == std::string::npos) break;
        out.emplace_back(bestPos, bestLen);
        from = bestPos + bestLen;
    }
    return out;
}

bool Matcher::matches(const std::string& line) const {
    const std::string hay = opts_.ignoreCase ? toLower(line) : line;
    bool found = std::any_of(needles_.begin(), needles_.end(),
                             [&](const std::string& n) { return contains(hay, n); });
    return found != opts_.invert;
}

std::size_t scan(std::istream& in, std::ostream& out, const Matcher& m,
                 const std::string& label) {
    const Options& o = m.options();
    const bool context = !o.countOnly && !o.onlyMatching &&
                         (o.afterContext > 0 || o.beforeContext > 0);
    std::size_t matched = 0, lineNo = 0;
    std::size_t offset = 0;       // byte offset of the start of the current line
    std::size_t nextOffset = 0;   // byte offset of the line after it
    std::size_t afterLeft = 0;    // trailing context lines still to print
    std::size_t lastPrinted = 0;  // line number of the last printed line, 0 = none
    bool limitReached = false;
    std::string line;
    // Recent unprinted lines that may become leading context for the next match.
    struct Pending {
        std::size_t lineNo, offset;
        std::string text;
    };
    std::deque<Pending> before;

    // Writes one output line; sep is ':' for selected lines, '-' for context.
    auto emit = [&](std::size_t n, std::size_t at, const std::string& text, char sep) {
        if (context && lastPrinted != 0 && n > lastPrinted + 1) out << "--\n";
        if (!label.empty()) out << label << sep;
        if (o.lineNumbers) out << n << sep;
        if (o.byteOffset) out << at << sep;
        out << text << '\n';
        lastPrinted = n;
    };

    while (std::getline(in, line)) {
        ++lineNo;
        offset = nextOffset;
        nextOffset = offset + line.size() + (in.eof() ? 0 : 1);
        if (limitReached || !m.matches(line)) {
            if (afterLeft > 0) {
                emit(lineNo, offset, line, '-');
                --afterLeft;
            } else if (context && o.beforeContext > 0) {
                before.push_back({lineNo, offset, line});
                if (before.size() > o.beforeContext) before.pop_front();
            }
            if (limitReached && afterLeft == 0) break;
            continue;
        }
        ++matched;
        if (o.countOnly) {
            // nothing to print per line
        } else if (o.onlyMatching) {
            if (!o.invert) {  // an unmatched line has no parts to print
                for (const auto& [start, len] : m.spans(line)) {
                    if (!label.empty()) out << label << ':';
                    if (o.lineNumbers) out << lineNo << ':';
                    if (o.byteOffset) out << offset + start << ':';
                    out << line.substr(start, len) << '\n';
                }
            }
        } else {
            for (const Pending& p : before) emit(p.lineNo, p.offset, p.text, '-');
            before.clear();
            emit(lineNo, offset, line, ':');
            afterLeft = context ? o.afterContext : 0;
        }
        if (o.maxCount != 0 && matched >= o.maxCount) {
            limitReached = true;
            if (afterLeft == 0) break;
        }
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
