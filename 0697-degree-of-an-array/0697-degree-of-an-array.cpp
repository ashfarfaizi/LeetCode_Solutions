/*
 * Approach: One pass recording, for each value, its count and first index.
 * Whenever a value's count reaches a new maximum, or ties it with a shorter
 * span, update the answer with the span from its first index to here.
 * Time: O(n), Space: O(n)
 */
class Solution {
public:
    int findShortestSubArray(vector<int>& nums) {
        unordered_map<int, int> count, first;
        int degree = 0, best = 0;
        for (int i = 0; i < (int)nums.size(); ++i) {
            int x = nums[i];
            if (!first.count(x)) first[x] = i;
            int c = ++count[x];
            int span = i - first[x] + 1;
            if (c > degree || (c == degree && span < best)) {
                degree = c;
                best = span;
            }
        }
        return best;
    }
};
