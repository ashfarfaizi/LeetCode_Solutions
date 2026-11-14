/*
 * Approach: Record the last index of every letter. Sweep left to right,
 * extending the current piece's end to the furthest last-occurrence seen so
 * far; when the sweep reaches that end, the piece can be closed.
 * Time: O(n), Space: O(1) (26-letter table)
 */
class Solution {
public:
    vector<int> partitionLabels(string s) {
        array<int, 26> last{};
        for (int i = 0; i < (int)s.size(); ++i) last[s[i] - 'a'] = i;

        vector<int> sizes;
        int start = 0, end = 0;
        for (int i = 0; i < (int)s.size(); ++i) {
            end = max(end, last[s[i] - 'a']);
            if (i == end) {
                sizes.push_back(end - start + 1);
                start = i + 1;
            }
        }
        return sizes;
    }
};
