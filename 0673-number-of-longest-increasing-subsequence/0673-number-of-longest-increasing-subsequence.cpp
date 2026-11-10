/*
 * Approach: DP. len[i] is the length of the longest increasing subsequence
 * ending at i and cnt[i] how many such subsequences there are. For each j < i
 * with nums[j] < nums[i], extending j either sets a new best length (take
 * cnt[j]) or ties it (add cnt[j]). Sum cnt over positions with the max length.
 * Time: O(n^2), Space: O(n)
 */
class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        int n = nums.size(), best = 0, total = 0;
        vector<int> len(n, 1), cnt(n, 1);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                if (nums[j] >= nums[i]) continue;
                if (len[j] + 1 > len[i]) {
                    len[i] = len[j] + 1;
                    cnt[i] = cnt[j];
                } else if (len[j] + 1 == len[i]) {
                    cnt[i] += cnt[j];
                }
            }
            if (len[i] > best) {
                best = len[i];
                total = cnt[i];
            } else if (len[i] == best) {
                total += cnt[i];
            }
        }
        return total;
    }
};
