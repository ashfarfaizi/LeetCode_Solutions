/*
 * Approach: Any match of b inside repeated a must start within the first
 * copy of a, so it needs at most ceil(|b| / |a|) + 1 copies. Build the
 * string with ceil(|b| / |a|) copies, test, then test once more with one
 * extra copy.
 * Time: O(|a| * (|a| + |b|)) with std::string::find, Space: O(|a| + |b|)
 */
class Solution {
public:
    int repeatedStringMatch(string a, string b) {
        int count = 1;
        string s = a;
        while (s.size() < b.size()) {
            s += a;
            ++count;
        }
        if (s.find(b) != string::npos) return count;
        s += a;
        if (s.find(b) != string::npos) return count + 1;
        return -1;
    }
};
