/*
 * Approach: Since the array is a permutation of 0..n-1, the prefix arr[0..i]
 * can be closed as a chunk exactly when its maximum equals i (it then holds
 * precisely the values 0..i). Count those positions.
 * Time: O(n), Space: O(1)
 */
class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        int chunks = 0, runningMax = -1;
        for (int i = 0; i < (int)arr.size(); ++i) {
            runningMax = max(runningMax, arr[i]);
            if (runningMax == i) ++chunks;
        }
        return chunks;
    }
};
