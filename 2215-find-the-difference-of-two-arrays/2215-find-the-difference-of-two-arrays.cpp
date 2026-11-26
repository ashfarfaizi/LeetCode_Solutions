/*
 * Approach: put each array into a hash set, then collect the elements of one
 * set that are missing from the other (sets already remove duplicates).
 * Time: O(n + m), Space: O(n + m)
 */
class Solution {
public:
    vector<vector<int>> findDifference(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> a(nums1.begin(), nums1.end());
        unordered_set<int> b(nums2.begin(), nums2.end());
        vector<vector<int>> res(2);
        for (int x : a) if (!b.count(x)) res[0].push_back(x);
        for (int x : b) if (!a.count(x)) res[1].push_back(x);
        return res;
    }
};
