class Solution {
public:
    int rangeBitwiseAnd(int left, int right) {
        int shift = 0;
        // Shift both numbers to the right until they are equal
        while (left < right) {
            left >>= 1;
            right >>= 1;
            shift++;
        }
        // Shift back to the left to restore the trailing zeros
        return left << shift;
    }
};
