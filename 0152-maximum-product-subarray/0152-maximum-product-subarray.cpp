#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        if (nums.empty()) return 0;
        
        int global_max = nums[0];
        int curr_max = nums[0];
        int curr_min = nums[0];
        
        for (size_t i = 1; i < nums.size(); ++i) {
            int num = nums[i];
            
            // If the current number is negative, max and min values swap 
            // when multiplied by a negative scale factor.
            if (num < 0) {
                swap(curr_max, curr_min);
            }
            
            // The choice is to either start a new subarray at num,
            // or continue the existing subarray product.
            curr_max = max(num, curr_max * num);
            curr_min = min(num, curr_min * num);
            
            // Maintain the highest peak found so far
            global_max = max(global_max, curr_max);
        }
        
        return global_max;
    }
};
