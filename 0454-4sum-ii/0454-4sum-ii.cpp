#include <vector>
#include <unordered_map>

class Solution {
public:
    int fourSumCount(std::vector<int>& nums1, std::vector<int>& nums2, std::vector<int>& nums3, std::vector<int>& nums4) {
        std::unordered_map<int, int> sum_counts;
        int count = 0;
        
        // Step 1: Store all sum combinations of nums1 and nums2
        for (int a : nums1) {
            for (int b : nums2) {
                sum_counts[a + b]++;
            }
        }
        
        // Step 2: Find complement sums in nums3 and nums4
        for (int c : nums3) {
            for (int d : nums4) {
                int target = -(c + d);
                if (sum_counts.count(target)) {
                    count += sum_counts[target];
                }
            }
        }
        
        return count;
    }
};
