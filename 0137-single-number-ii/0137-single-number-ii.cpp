class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int result = 0;
        
        // Iterate through all 32 bit positions
        for (int i = 0; i < 32; i++) {
            int bit_sum = 0;
            
            // Count how many numbers have the i-th bit set
            for (int num : nums) {
                if ((num >> i) & 1) {
                    bit_sum++;
                }
            }
            
            // If the sum is not a multiple of 3, this bit belongs to the answer
            if (bit_sum % 3 != 0) {
                result |= (1 << i);
            }
        }
        
        return result;
    }
};
