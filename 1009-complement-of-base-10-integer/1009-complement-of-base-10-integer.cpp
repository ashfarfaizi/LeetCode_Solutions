/*
 * Approach: build a mask of all 1s covering n's significant bits, then XOR.
 * Time: O(log n)   Space: O(1)
 */
class Solution {
public:
    int bitwiseComplement(int n) {
        if (n == 0) return 1;
        unsigned mask = 0;
        for (unsigned x = n; x; x >>= 1) mask = (mask << 1) | 1u;
        return static_cast<int>(mask ^ static_cast<unsigned>(n));
    }
};
