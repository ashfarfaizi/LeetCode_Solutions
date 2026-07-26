class Solution {
public:
    int maximumProduct(vector<int>& nums) {
        int hi1 = INT_MIN, hi2 = INT_MIN, hi3 = INT_MIN;
        int lo1 = INT_MAX, lo2 = INT_MAX;

        for (int x : nums) {
            if (x >= hi1) {
                hi3 = hi2;
                hi2 = hi1;
                hi1 = x;
            } else if (x >= hi2) {
                hi3 = hi2;
                hi2 = x;
            } else if (x > hi3) {
                hi3 = x;
            }

            if (x <= lo1) {
                lo2 = lo1;
                lo1 = x;
            } else if (x < lo2) {
                lo2 = x;
            }
        }

        int threeLargest = hi1 * hi2 * hi3;
        int twoSmallestAndLargest = lo1 * lo2 * hi1;

        return max(threeLargest, twoSmallestAndLargest);
    }
};