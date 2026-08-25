class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int left = 0;
        int right = nums.size() - 1;

        while (left < right) {
            int mid = left + (right - left) / 2;

            // If mid is less than its right neighbor, the peak is in the right half
            if (nums[mid] < nums[mid + 1]) {
                left = mid + 1;
            } 
            // Otherwise, mid is part of a descending slope; peak is at mid or to the left
            else {
                right = mid;
            }
        }

        // Left and right converge to a valid peak element index
        return left;
    }
};
