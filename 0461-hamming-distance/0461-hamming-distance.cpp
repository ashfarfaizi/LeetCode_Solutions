class Solution {
public:
    int hammingDistance(int x, int y) {
        // XOR gives 1 where bits differ; __builtin_popcount counts those 1s
        return __builtin_popcount(x ^ y);
    }
};
