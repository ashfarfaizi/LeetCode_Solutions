#include <vector>

using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        // Elements at index 0 and 1 are always allowed to stay
        if (nums.size() <= 2) {
            return nums.size();
        }

        int k = 2; // Pointer for the next valid slot to write into

        // Iterate through the array starting from the third element
        for (int n = 2; n < nums.size(); ++n) {
            // Compare current element with the element 2 positions behind the write head
            if (nums[n] != nums[k - 2]) {
                nums[k] = nums[n];
                k++;
            }
        }

        return k; // Return total count of valid elements
    }
};
