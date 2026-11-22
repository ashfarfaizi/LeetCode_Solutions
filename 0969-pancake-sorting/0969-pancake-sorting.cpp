/*
 * Approach: selection sort with flips. For each size s from n down to 2, the
 * value s (arr is a permutation of 1..n) belongs at index s-1. Find where it
 * currently sits at index i; flip the first i+1 elements to bring it to the
 * front, then flip the first s elements to drop it into place. Skip both
 * flips when it is already in position. Uses at most 2n flips.
 *
 * Time:  O(n^2)
 * Space: O(1) extra besides the answer
 */
class Solution {
public:
    vector<int> pancakeSort(vector<int>& arr) {
        vector<int> flips;
        for (int s = arr.size(); s >= 2; --s) {
            int i = find(arr.begin(), arr.begin() + s, s) - arr.begin();
            if (i == s - 1) continue;
            if (i > 0) {
                reverse(arr.begin(), arr.begin() + i + 1);
                flips.push_back(i + 1);
            }
            reverse(arr.begin(), arr.begin() + s);
            flips.push_back(s);
        }
        return flips;
    }
};
