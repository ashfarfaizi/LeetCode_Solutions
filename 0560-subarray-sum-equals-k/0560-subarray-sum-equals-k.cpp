/*
 * Approach: Prefix sums + hash map. A subarray (j, i] sums to k exactly when
 * prefix[i] - prefix[j] == k, so for each prefix we add how many earlier
 * prefixes equal prefix - k. Seed the map with {0: 1} for subarrays starting
 * at index 0. Works with negative numbers, unlike a sliding window.
 * Time: O(n), Space: O(n)
 */
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> seen{{0, 1}};
        int prefix = 0, count = 0;
        for (int x : nums) {
            prefix += x;
            auto it = seen.find(prefix - k);
            if (it != seen.end()) count += it->second;
            ++seen[prefix];
        }
        return count;
    }
};
