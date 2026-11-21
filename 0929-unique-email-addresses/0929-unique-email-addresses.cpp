/*
 * Approach: normalise each address and count distinct results with a hash
 * set. In the local part (before '@') drop every '.' and ignore everything
 * from the first '+'; the domain is kept unchanged.
 *
 * Time:  O(total length of all emails)
 * Space: O(total length of all emails)
 */
class Solution {
public:
    int numUniqueEmails(vector<string>& emails) {
        unordered_set<string> seen;
        for (const string& e : emails) {
            size_t at = e.find('@');
            string local;
            for (size_t i = 0; i < at && e[i] != '+'; ++i) {
                if (e[i] != '.') local += e[i];
            }
            seen.insert(local + e.substr(at));
        }
        return seen.size();
    }
};
