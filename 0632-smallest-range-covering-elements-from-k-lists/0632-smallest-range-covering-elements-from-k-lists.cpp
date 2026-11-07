/*
 * Approach: K-way merge with a min-heap. Keep one pointer per list and push
 * the current element of each into a min-heap while tracking the current
 * maximum. [heap top, max] always covers every list; record it, then advance
 * the list that owns the minimum. Stop when any list runs out.
 * Time: O(N log k) for N total elements, Space: O(k)
 */
class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        using Item = tuple<int, int, int>;  // value, list index, element index
        priority_queue<Item, vector<Item>, greater<Item>> heap;
        int curMax = INT_MIN;
        for (int i = 0; i < (int)nums.size(); ++i) {
            heap.emplace(nums[i][0], i, 0);
            curMax = max(curMax, nums[i][0]);
        }
        int bestLo = get<0>(heap.top()), bestHi = curMax;
        while (true) {
            auto [value, list, idx] = heap.top();
            heap.pop();
            if ((long long)curMax - value < (long long)bestHi - bestLo) {
                bestLo = value;
                bestHi = curMax;
            }
            if (idx + 1 == (int)nums[list].size()) break;
            int next = nums[list][idx + 1];
            heap.emplace(next, list, idx + 1);
            curMax = max(curMax, next);
        }
        return {bestLo, bestHi};
    }
};
