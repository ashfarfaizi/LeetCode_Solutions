class Solution {
public:
    bool isPowerOfTwo(int n) {
        // A power of two must be strictly greater than zero 
        // and have exactly one set bit in its binary representation.
        return n > 0 && (n & (n - 1)) == 0;
    }
};
