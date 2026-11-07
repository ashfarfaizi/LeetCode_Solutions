/*
 * Approach: Prime factorisation. Building n characters is a sequence of
 * "copy all, paste p - 1 times" blocks, each multiplying the length by p for
 * a cost of p steps. Splitting a factor never costs more, so the answer is
 * the sum of the prime factors of n (with multiplicity).
 * Time: O(sqrt n), Space: O(1)
 */
class Solution {
public:
    int minSteps(int n) {
        int steps = 0;
        for (int d = 2; d * d <= n; ++d) {
            while (n % d == 0) {
                steps += d;
                n /= d;
            }
        }
        if (n > 1) steps += n;
        return steps;
    }
};
