/*
 * Approach: Greedy. Track the farthest index reachable so far while scanning
 * left to right. If the current index is beyond that reach, we are stuck.
 * Time: O(n), Space: O(1)
 */
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int reach = 0;
        for (int i = 0; i < (int)nums.size(); ++i) {
            if (i > reach) return false;
            reach = max(reach, i + nums[i]);
            if (reach >= (int)nums.size() - 1) return true;
        }
        return true;
    }
};
