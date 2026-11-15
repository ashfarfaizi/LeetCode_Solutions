/*
 * Approach: Binary search on the fraction value x in (0, 1). For a given x,
 * a two-pointer sweep counts fractions <= x and tracks the largest such
 * fraction. When the count equals k, that largest fraction is the answer.
 * Time: O(n log W) for the search iterations, Space: O(1)
 */
class Solution {
public:
    vector<int> kthSmallestPrimeFraction(vector<int>& arr, int k) {
        int n = arr.size();
        double lo = 0.0, hi = 1.0;
        while (true) {
            double mid = (lo + hi) / 2;
            int count = 0, p = 0, q = 1;
            for (int i = 0, j = 1; i < n - 1; ++i) {
                while (j < n && arr[i] > mid * arr[j]) ++j;
                if (j == n) break;
                count += n - j;
                if ((long long)arr[i] * q > (long long)p * arr[j]) {
                    p = arr[i];
                    q = arr[j];
                }
            }
            if (count == k) return {p, q};
            if (count < k) lo = mid;
            else hi = mid;
        }
    }
};
