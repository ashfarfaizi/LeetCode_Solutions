#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    void sortColors(vector<int>& nums) {
        int low = 0;
        int mid = 0;
        int high = nums.size() - 1;

        while (mid <= high) {
            if (nums[mid] == 0) {
                // Swap the current 0 with the element at the low boundary
                swap(nums[mid], nums[low]);
                low++;
                mid++;
            } 
            else if (nums[mid] == 1) {
                // 1s belong in the middle section, just move the runner forward
                mid++;
            } 
            else { // nums[mid] == 2
                // Swap the current 2 with the element at the high boundary
                swap(nums[mid], nums[high]);
                high--;
                // Do not increment mid here; evaluate the swapped element next
            }
        }
    }
};
