#include <vector>

class Solution {
public:
    int findDuplicate(std::vector<int>& nums) {
        // Phase 1: Detect that a cycle exists
        int slow = nums[0];
        int fast = nums[0];
        
        do {
            slow = nums[slow];          // Moves 1 step
            fast = nums[nums[fast]];    // Moves 2 steps
        } while (slow != fast);
        
        // Phase 2: Find the entrance to the cycle (the duplicate element)
        slow = nums[0];                 // Reset slow to start
        while (slow != fast) {
            slow = nums[slow];          // Both move 1 step now
            fast = nums[fast];
        }
        
        return slow; // or fast, both point to the duplicate
    }
};
