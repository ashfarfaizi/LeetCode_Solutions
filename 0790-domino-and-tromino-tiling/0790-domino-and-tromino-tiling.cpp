/*
 * Approach: Let f[i] be the number of tilings of a 2 x i board. Splitting on
 * the shape that covers the last column gives f[i] = 2 * f[i-1] + f[i-3],
 * with f[0] = 1, f[1] = 1, f[2] = 2. Keep only the last three values.
 * Time: O(n), Space: O(1)
 */
class Solution {
public:
    int numTilings(int n) {
        const long long MOD = 1'000'000'007;
        if (n <= 2) return n;
        long long a = 1, b = 1, c = 2;  // f[i-3], f[i-2], f[i-1]
        for (int i = 3; i <= n; ++i) {
            long long d = (2 * c + a) % MOD;
            a = b;
            b = c;
            c = d;
        }
        return (int)c;
    }
};
