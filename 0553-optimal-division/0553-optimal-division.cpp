/*
 * Approach: Math. The first number is always the numerator and the second
 * is always in the denominator. Dividing the second by every remaining number
 * makes the denominator as small as possible (all values are >= 2), so the
 * answer is a/(b/c/d/...). With one or two numbers no parentheses are needed.
 * Time: O(n), Space: O(n) for the output string
 */
class Solution {
public:
    string optimalDivision(vector<int>& nums) {
        int n = nums.size();
        string res = to_string(nums[0]);
        if (n == 1) return res;
        if (n == 2) return res + "/" + to_string(nums[1]);
        res += "/(" + to_string(nums[1]);
        for (int i = 2; i < n; ++i) res += "/" + to_string(nums[i]);
        return res + ")";
    }
};
