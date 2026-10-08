#include <vector>
#include <cmath>

class Solution {
private:
    // Helper function to calculate the next index in a circular array
    int getNext(int curr, const std::vector<int>& nums, int n) {
        int next_idx = (curr + nums[curr]) % n;
        if (next_idx < 0) {
            next_idx += n; // Handle negative modulo in C++
        }
        return next_idx;
    }

public:
    bool circularArrayLoop(std::vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) return false;

        for (int i = 0; i < n; i++) {
            // If the element is 0, it belongs to an already checked failing path
            if (nums[i] == 0) continue;

            int slow = i;
            int fast = i;
            bool is_forward = nums[i] > 0;

            // Floyd's Cycle Detection Loop
            while (true) {
                // Advance slow by 1 step
                slow = getNext(slow, nums, n);
                if ((nums[slow] > 0) != is_forward || nums[slow] == 0) break;

                // Advance fast by 2 steps
                fast = getNext(fast, nums, n);
                if ((nums[fast] > 0) != is_forward || nums[fast] == 0) break;
                
                fast = getNext(fast, nums, n);
                if ((nums[fast] > 0) != is_forward || nums[fast] == 0) break;

                // Cycle found
                if (slow == fast) {
                    // Check if it's a self-loop (cycle of length 1)
                    if (slow == getNext(slow, nums, n)) {
                        break; 
                    }
                    return true;
                }
            }

            // Optimization: Mark all invalid nodes on this path as 0 so we don't recheck them
            int curr = i;
            while ((nums[curr] > 0) == is_forward && nums[curr] != 0) {
                int next_node = getNext(curr, nums, n);
                nums[curr] = 0;
                curr = next_node;
            }
        }

        return false;
    }
};
