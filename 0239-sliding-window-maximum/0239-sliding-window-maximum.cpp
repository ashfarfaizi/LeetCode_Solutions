#include <vector>
#include <deque>

class Solution {
public:
    std::vector<int> maxSlidingWindow(std::vector<int>& nums, int k) {
        std::vector<int> result;
        std::deque<int> dq; // Stores indices of elements
        
        for (int i = 0; i < nums.size(); ++i) {
            // 1. Remove indices that are out of the current sliding window bounds
            if (!dq.empty() && dq.front() == i - k) {
                dq.pop_front();
            }
            
            // 2. Maintain monotonic property: remove elements smaller than the current element
            while (!dq.empty() && nums[dq.back()] < nums[i]) {
                dq.pop_back();
            }
            
            // 3. Add the current element's index
            dq.push_back(i);
            
            // 4. The front of the deque is always the maximum element for the current window
            if (i >= k - 1) {
                result.push_back(nums[dq.front()]);
            }
        }
        
        return result;
    }
};
