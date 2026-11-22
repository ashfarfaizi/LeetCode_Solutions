/*
 * Approach: prefix sums modulo k. A subarray (i, j] has a sum divisible by k
 * exactly when prefix[i] and prefix[j] leave the same remainder. Keep a count
 * of each remainder seen so far (starting with remainder 0 once for the empty
 * prefix) and add the count of the current remainder at every step. The
 * remainder is normalised to [0, k) because C++ % can be negative.
 *
 * Time:  O(n)
 * Space: O(k)
 */
class Solution {
public:
    int subarraysDivByK(vector<int>& nums, int k) {
        vector<int> count(k, 0);
        count[0] = 1;
        int prefix = 0, result = 0;
        for (int x : nums) {
            prefix = ((prefix + x) % k + k) % k;
            result += count[prefix]++;
        }
        return result;
    }
};
