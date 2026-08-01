class Solution {
public:
    int solve(vector<int>& nums, int left, int right, vector<vector<int>>& dp) {
        if (left == right)
            return nums[left];

        if (dp[left][right] != INT_MIN)
            return dp[left][right];

        int takeLeft = nums[left] - solve(nums, left + 1, right, dp);
        int takeRight = nums[right] - solve(nums, left, right - 1, dp);

        return dp[left][right] = max(takeLeft, takeRight);
    }

    bool predictTheWinner(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> dp(n, vector<int>(n, INT_MIN));

        return solve(nums, 0, n - 1, dp) >= 0;
    }
};