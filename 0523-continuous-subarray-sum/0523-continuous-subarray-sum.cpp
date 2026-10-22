#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> remainder_map;
        remainder_map[0] = -1;
        
        int prefix_sum = 0;
        for (int i = 0; i < nums.size(); i++) {
            prefix_sum += nums[i];
            int remainder = prefix_sum % k;
            
            if (remainder_map.count(remainder)) {
                if (i - remainder_map[remainder] >= 2) {
                    return true;
                }
            } else {
                remainder_map[remainder] = i;
            }
        }
        
        return false;
    }
};
