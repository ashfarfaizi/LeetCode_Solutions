#include <vector>

class Solution {
public:
    std::vector<int> singleNumber(std::vector<int>& nums) {
        // Step 1: XOR all numbers to get x ^ y
        long long xor_sum = 0; // Use long long to avoid overflow when getting the lowest bit of INT_MIN
        for (int num : nums) {
            xor_sum ^= num;
        }
        
        // Step 2: Extract the lowest set bit (rightmost 1-bit)
        long long lowest_bit = xor_sum & -xor_sum;
        
        // Step 3: Divide numbers into two groups and find the unique elements
        int num1 = 0;
        int num2 = 0;
        for (int num : nums) {
            if (num & lowest_bit) {
                num1 ^= num; // Group where the bit is set
            } else {
                num2 ^= num; // Group where the bit is not set
            }
        }
        
        return {num1, num2};
    }
};
