/*
 * Approach: sort index pairs by nums2 descending so the current pair's nums2
 * is the minimum of everything chosen so far. Keep the k largest nums1 values
 * seen in a min-heap with their running sum; whenever the heap holds k items,
 * sum * current nums2 is a candidate score.
 * Time: O(n log n), Space: O(n)
 */
class Solution {
public:
    long long maxScore(vector<int>& nums1, vector<int>& nums2, int k) {
        int n = nums1.size();
        vector<pair<int, int>> pairs(n);  // (nums2, nums1)
        for (int i = 0; i < n; ++i) pairs[i] = {nums2[i], nums1[i]};
        sort(pairs.rbegin(), pairs.rend());
        priority_queue<int, vector<int>, greater<int>> heap;
        long long sum = 0, best = 0;
        for (auto [mn, v] : pairs) {
            heap.push(v);
            sum += v;
            if ((int)heap.size() > k) {
                sum -= heap.top();
                heap.pop();
            }
            if ((int)heap.size() == k) best = max(best, sum * mn);
        }
        return best;
    }
};
