#include <vector>
#include <algorithm>

class Solution {
public:
    std::vector<int> maxNumber(std::vector<int>& nums1, std::vector<int>& nums2, int k) {
        int m = nums1.size();
        int n = nums2.size();
        std::vector<int> max_result;

        // Try all valid number of elements taken from nums1
        int start = std::max(0, k - n);
        int end = std::min(k, m);

        for (int i = start; i <= end; ++i) {
            std::vector<int> sub1 = maxSubarray(nums1, i);
            std::vector<int> sub2 = maxSubarray(nums2, k - i);
            std::vector<int> current_merge = merge(sub1, sub2);
            
            // Track the globally maximum lexicographical vector
            if (current_merge > max_result) {
                max_result = current_merge;
            }
        }

        return max_result;
    }

private:
    // Helper function to get the maximum number of length x from a single array
    std::vector<int> maxSubarray(const std::vector<int>& nums, int x) {
        std::vector<int> result;
        int drop = nums.size() - x; // Total elements we are allowed to discard

        for (int num : nums) {
            while (drop > 0 && !result.empty() && result.back() < num) {
                result.pop_back();
                drop--;
            }
            result.push_back(num);
        }
        
        // Resize to ensure exactly x elements are kept
        result.resize(x);
        return result;
    }

    // Helper function to merge two arrays to create the maximum lexicographical number
    std::vector<int> merge(const std::vector<int>& sub1, const std::vector<int>& sub2) {
        std::vector<int> result;
        auto it1 = sub1.begin();
        auto it2 = sub2.begin();

        while (it1 != sub1.end() || it2 != sub2.end()) {
            // std::lexicographical_compare / vector comparison handles suffix prioritization
            if (std::vector<int>(it1, sub1.end()) > std::vector<int>(it2, sub2.end())) {
                result.push_back(*it1++);
            } else {
                result.push_back(*it2++);
            }
        }
        return result;
    }
};
