class Solution {
public:
    bool isPowerOfThree(int n) {
        // 1162261467 is 3^19, the maximum power of 3 that fits in a 32-bit signed integer.
        return n > 0 && 1162261467 % n == 0;
    }
};
