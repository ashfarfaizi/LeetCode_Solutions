class Solution {
public:
    int trailingZeroes(int n) {
        int count = 0;
        
        // Loop runs in logarithmic time by dividing n by 5 at each step
        while (n >= 5) {
            count += n / 5;
            n /= 5;
        }
        
        return count;
    }
};
