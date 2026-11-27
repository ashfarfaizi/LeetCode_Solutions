/*
 * Approach: examine each bit independently. If c's bit is 1 we need one flip
 * only when both a and b have 0; if c's bit is 0 every set bit among a and b
 * must be flipped.
 * Time: O(log max(a, b, c)), Space: O(1)
 */
class Solution {
public:
    int minFlips(int a, int b, int c) {
        int flips = 0;
        while (a || b || c) {
            int x = a & 1, y = b & 1, z = c & 1;
            if (z) flips += !(x | y);
            else flips += x + y;
            a >>= 1;
            b >>= 1;
            c >>= 1;
        }
        return flips;
    }
};
