class Solution {
public:
    int hammingWeight(int n) {
        return __builtin_popcount(n); // Executes in a single CPU cycle
    }
};
