/*
 * Approach: binary search on the capacity in [max weight, sum of weights];
 * greedily count the days needed for a candidate capacity.
 * Time: O(n log(sum))   Space: O(1)
 */
class Solution {
public:
    int shipWithinDays(vector<int>& weights, int days) {
        int lo = *max_element(weights.begin(), weights.end());
        int hi = accumulate(weights.begin(), weights.end(), 0);
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (daysNeeded(weights, mid) <= days) hi = mid;
            else lo = mid + 1;
        }
        return lo;
    }

private:
    int daysNeeded(const vector<int>& w, int cap) {
        int d = 1, load = 0;
        for (int x : w) {
            if (load + x > cap) { d++; load = 0; }
            load += x;
        }
        return d;
    }
};
