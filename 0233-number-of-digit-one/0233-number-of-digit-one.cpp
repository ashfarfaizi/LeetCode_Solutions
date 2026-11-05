/*
 * Approach: Count the contribution of each decimal position separately. For a
 * position with weight m, split n into high = n / (m*10), cur = (n / m) % 10 and
 * low = n % m. That position shows a 1 high*m times from full cycles, plus m more
 * if cur > 1, or low + 1 more if cur == 1.
 * Time: O(log n), Space: O(1)
 */
class Solution {
public:
    int countDigitOne(int n) {
        long long count = 0;
        for (long long m = 1; m <= n; m *= 10) {
            long long high = n / (m * 10), cur = (n / m) % 10, low = n % m;
            count += high * m;
            if (cur > 1) count += m;
            else if (cur == 1) count += low + 1;
        }
        return static_cast<int>(count);
    }
};
