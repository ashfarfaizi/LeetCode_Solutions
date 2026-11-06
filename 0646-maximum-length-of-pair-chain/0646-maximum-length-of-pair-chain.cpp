/*
 * Approach: Greedy, like interval scheduling. Sort pairs by their right end
 * and take a pair whenever its left end is strictly greater than the right
 * end of the last pair taken; finishing early leaves the most room.
 * Time: O(n log n), Space: O(1) besides sorting
 */
class Solution {
public:
    int findLongestChain(vector<vector<int>>& pairs) {
        sort(pairs.begin(), pairs.end(),
             [](const vector<int>& a, const vector<int>& b) { return a[1] < b[1]; });
        int length = 0;
        long long lastEnd = LLONG_MIN;
        for (auto& p : pairs) {
            if (p[0] > lastEnd) {
                ++length;
                lastEnd = p[1];
            }
        }
        return length;
    }
};
